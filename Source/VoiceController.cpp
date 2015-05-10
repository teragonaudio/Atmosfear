/*
  ==============================================================================

    VoiceController.cpp
    Created: 9 May 2015 12:55:47pm
    Author:  nik

  ==============================================================================
*/

#include "VoiceController.h"

using namespace teragon;

VoiceController::VoiceController(teragon::ConcurrentParameterSet &ps,
                                 const double sr) :
        parameters(ps),
        sampleRate(sr > 0 ? sr : 44100)
{
    for (size_t voiceNumber = 0; voiceNumber < kMaxVoiceCount; ++voiceNumber) {
        voiceBuffers[voiceNumber].clear();
        sampleOffsets[voiceNumber] = 0;
    }
}

void VoiceController::filesAdded(std::vector<AudioSampleBuffer> *inVoiceBuffers) {
    for (size_t voiceNumber = 0; voiceNumber < kMaxVoiceCount; ++voiceNumber) {
        for (size_t i = 0; i < inVoiceBuffers[voiceNumber].size(); ++i) {
            voiceBuffers[voiceNumber].push_back(inVoiceBuffers[voiceNumber][i]);
        }
    }
}

void VoiceController::process(AudioSampleBuffer &buffer) {
    for (size_t voiceNumber = 0; voiceNumber < kMaxVoiceCount; ++voiceNumber) {
        triggerVoice(voiceNumber);
        processVoice(buffer, voiceNumber);
    }
}

void VoiceController::triggerVoice(size_t voiceNumber) {
    Parameter *enabled = parameters.get(getVoiceParamName("Enabled", voiceNumber));

    if (enabled->getValue()) {
        Parameter *ready = parameters.get(getVoiceParamName("Ready", voiceNumber));
        if (!ready->getValue()) {
            // No samples loaded yet for this voice
            return;
        }

        Parameter *playing = parameters.get(getVoiceParamName("Playing", voiceNumber));
        if (playing->getValue()) {
            // If we're already playing a sample on this voice, then bail out
            return;
        }

        Parameter *triggered = parameters.get(getVoiceParamName("Triggered", voiceNumber));
        if (triggered->getValue()) {
            // Same goes for the triggered parameter (note: this is unlikely to occur)
            return;
        }

        Parameter *cooldown = parameters.get(getVoiceParamName("Cooldown", voiceNumber));
        if (cooldown->getValue() > kMinPeriodInSec) {
            // If the cooldown value is greater than zero, it means that we explicitly
            // should not schedule another trigger during this period. This value will
            // be decremented in processVoice() until it reaches 0.
            return;
        }

        // Generate a random value and see if it is *less* than the parameter for the
        // randomness which we have set for the voice. This determines the likelihood
        // that we should play the sample this block.
        Parameter *randomness = parameters.get(getVoiceParamName("Randomness", voiceNumber));
        const int randomValue = randomGenerator.nextInt(kMaxRandomness);
        if (randomValue < randomness->getValue()) {
            printf("Triggering sample for voice %ld\n", voiceNumber);
            // Yay! If we made it here, then trigger the sample
            parameters.set(triggered, true);
        }
    }
}

void VoiceController::processVoice(AudioSampleBuffer &buffer, size_t voiceNumber) {
    Parameter *enabled = parameters.get(getVoiceParamName("Enabled", voiceNumber));
    if (enabled->getValue()) {
        Parameter *ready = parameters.get(getVoiceParamName("Ready", voiceNumber));
        if (!ready->getValue()) {
            // Check the directory on disk and see if there are samples waiting for us.
            // If so, then load one of the samples into our voice's sample buffer, and
            // then set the ready parameter to be true.
            if (!voiceBuffers[voiceNumber].empty()) {
                parameters.set(ready, true);
                // Must call process directly afterwards to actually set the value
                parameters.processRealtimeEvents();
            }
        }

        // We have at least one sample loaded now
        if (ready->getValue()) {
            // Cache some parameters that we'll need below
            Parameter *playing = parameters.get(getVoiceParamName("Playing", voiceNumber));
            Parameter *triggered = parameters.get(getVoiceParamName("Triggered", voiceNumber));
            Parameter *cooldown = parameters.get(getVoiceParamName("Cooldown", voiceNumber));

            if (playing->getValue()) {
                if (playingVoiceBuffers[voiceNumber] == nullptr) {
                    // omg
                    return;
                }

                copySamples(buffer, *playingVoiceBuffers[voiceNumber], voiceNumber, parameters);

                if (sampleOffsets[voiceNumber] + buffer.getNumSamples() > playingVoiceBuffers[voiceNumber]->getNumSamples()) {
                    Parameter *period = parameters.get(getVoiceParamName("Period", voiceNumber));
                    // Set the cooldown to be the same as the period
                    parameters.set(cooldown, period->getValue());
                    parameters.set(playing, false);
                    sampleOffsets[voiceNumber] = 0;
                } else {
                    sampleOffsets[voiceNumber] += buffer.getNumSamples();
                }
            } else if (triggered->getValue()) {
                // If we've been triggered, then set the state to playing and set the
                // triggered parameter back to false. Note that we will actually start
                // playing in the next block.
                parameters.set(playing, true);
                parameters.set(triggered, false);

                // Pick a sample to play
                const size_t bufferIndex = (const size_t) randomGenerator.nextInt(
                        (int) voiceBuffers[voiceNumber].size());
                playingVoiceBuffers[voiceNumber] = &voiceBuffers[voiceNumber][bufferIndex];
            } else if (cooldown->getValue() > kMinPeriodInSec) {
                ParameterValue newValue = cooldown->getValue() -
                        (double)buffer.getNumSamples() / sampleRate;
                // Sanity check to make sure that this parameter doesn't end up being
                // negative. Not sure if that will have any ill effects, but IIRC the
                // ParameterSet doesn't do any bounds checking so better safe than sorry.
                if (newValue < kMinPeriodInSec) {
                    newValue = kMinPeriodInSec;
                }
                parameters.set(cooldown, newValue);
            }
        }
    }
}

void VoiceController::copySamples(AudioSampleBuffer &outBuffer,
                                  AudioSampleBuffer &voiceBuffer,
                                  size_t voiceNumber,
                                  ConcurrentParameterSet &voiceParameters) {
    // Desperate sanity check. For some reason, we get crazy voice buffers sometimes,
    // I suspect that this is caused by dangling pointers when we received file system
    // updates.
    if (voiceBuffer.getNumChannels() > kMaxVoiceCount || voiceBuffer.getNumSamples() < 0) {
        return;
    }

    // Cache some parameters outside of the inner loop
    Parameter *volume = parameters.get(getVoiceParamName("Volume", voiceNumber));
    double gain = volume->getValue();
    Parameter *panning = parameters.get(getVoiceParamName("Panning", voiceNumber));

    // Copy the voice sample buffer to the temporary scratch buffer
    int samplesToCopy = outBuffer.getNumSamples();
    if (sampleOffsets[voiceNumber] + outBuffer.getNumSamples() > voiceBuffer.getNumSamples()) {
        samplesToCopy = voiceBuffer.getNumSamples() - sampleOffsets[voiceNumber];
    }

    for (int channel = 0; channel < outBuffer.getNumChannels(); ++channel) {
        // Calculate panning/volume for each channel
        // TODO: Filter, reverb, etc. should be also processed here
        const double panningValue = panning->getValue();
        if (channel == 0) {  // Left channel
            if (panningValue > 0) {
                gain *= (1.0 - panningValue);
            }
        } else if (channel == 1) {  // Right channel
            if (panningValue < 0) {
                gain *= (1.0 - (panningValue * -1.0));
            }
        }

        if (gain > 1.0) {
            gain = 1.0;
        }

        outBuffer.addFrom(channel,
                          0,
                          voiceBuffer,
                          channel,
                          sampleOffsets[voiceNumber],
                          samplesToCopy,
                          (float) gain);
    }
}
