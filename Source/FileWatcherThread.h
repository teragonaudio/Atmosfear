/*
  ==============================================================================

    FileWatcherThread.h
    Created: 9 May 2015 5:52:33pm
    Author:  nik

  ==============================================================================
*/

#ifndef FILEWATCHERTHREAD_H_INCLUDED
#define FILEWATCHERTHREAD_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "../Third-Party/TeragonGuiComponents/Components/Source/TeragonGuiComponents.h"
#include "Constants.h"

class FileWatcherThread : public Thread {
public:
    FileWatcherThread(teragon::ConcurrentParameterSet &parameters);

    virtual void run();
    std::vector<AudioSampleBuffer> *getVoiceBuffers() { return voiceBuffers; }

private:
    bool scanDataDirectory(size_t voiceNumber);
    bool readDataFile(AudioSampleBuffer *buffer, File file);

private:
    std::vector<String> loadedSampleNames[kMaxVoiceCount];
    std::vector<AudioSampleBuffer> voiceBuffers[kMaxVoiceCount];
    teragon::ConcurrentParameterSet &parameters;
};

#endif  // FILEWATCHERTHREAD_H_INCLUDED
