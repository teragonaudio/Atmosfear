/*
  ==============================================================================

    VoiceController.h
    Created: 9 May 2015 12:55:47pm
    Author:  nik

  ==============================================================================
*/

#ifndef VOICECONTROLLER_H_INCLUDED
#define VOICECONTROLLER_H_INCLUDED

#include "../Third-Party/TeragonGuiComponents/Components/Source/TeragonGuiComponents.h"
#include "Constants.h"

class VoiceController {
public:
    VoiceController(teragon::ConcurrentParameterSet &ps,
                    const double sampleRate);

    void filesAdded(std::vector<AudioSampleBuffer> *inVoiceBuffers);
    void process(AudioSampleBuffer &buffer);

private:
    void triggerVoice(size_t voiceNumber);
    void processVoice(AudioSampleBuffer &buffer, size_t voiceNumber);
    void copySamples(AudioSampleBuffer &buffer,
                     AudioSampleBuffer &voiceBuffer,
                     size_t voiceNumber,
                     teragon::ConcurrentParameterSet &voiceParameters);

private:
    teragon::ConcurrentParameterSet &parameters;
    std::vector<AudioSampleBuffer> voiceBuffers[kMaxVoiceCount];
    AudioSampleBuffer *playingVoiceBuffers[kMaxVoiceCount];
    Random randomGenerator;
    int sampleOffsets[kMaxVoiceCount];
    const double sampleRate;
};

#endif  // VOICECONTROLLER_H_INCLUDED
