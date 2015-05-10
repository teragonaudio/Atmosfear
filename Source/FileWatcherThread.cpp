/*
  ==============================================================================

    FileWatcherThread.cpp
    Created: 9 May 2015 5:52:33pm
    Author:  nik

  ==============================================================================
*/

#include "FileWatcherThread.h"


FileWatcherThread::FileWatcherThread(teragon::ConcurrentParameterSet &p) :
        Thread("FileWatcher"),
        parameters(p)
{
}

void FileWatcherThread::run() {
    while (!threadShouldExit()) {
        File base_directory (kDatabasePath.substr(0, kDatabasePath.length() - 1));

        if (!base_directory.exists()) {
            printf("Creating base directory\n");
            base_directory.createDirectory();
        }

        for (size_t i = 0; i < kMaxVoiceCount; ++i) {
            if (scanDataDirectory(i)) {
                // Trigger sample loading on the main thread
                parameters.set("Files Added", true);
            }
        }

        sleep(200);
    }
}

bool FileWatcherThread::scanDataDirectory(size_t voiceNumber) {
    File directory(kDatabasePath + kDirPrefix + (char)((int) '0' + voiceNumber));

    if (!directory.exists()) {
        // printf("Creating subdirectory %ld\n", voiceNumber);
        directory.createDirectory();
        return false;
    }

    DirectoryIterator iterator(directory, "*");
    if (directory.exists()) {
        bool filesFound = false;
        while (iterator.next()) {
            File dataFile(iterator.getFile());
            std::vector<String> &voiceVector = loadedSampleNames[voiceNumber];
            std::vector<String>::iterator iter = std::find(voiceVector.begin(),
                                                           voiceVector.end(),
                                                           dataFile.getFileName());
            // Found this sample already
            if (iter != voiceVector.end()) {
                continue;
            }

            AudioSampleBuffer buffer;
            if (readDataFile(&buffer, dataFile)) {
                printf("Loaded file: %s\n", dataFile.getFileName().toRawUTF8());
                voiceVector.push_back(dataFile.getFileName());
                voiceBuffers[voiceNumber].push_back(buffer);
                filesFound = true;
            }
        }

        return filesFound;
    }

    return false;
}

bool FileWatcherThread::readDataFile(AudioSampleBuffer *buffer, File file) {
    AudioFormatManager formatManager;
    formatManager.registerBasicFormats();
    ScopedPointer<AudioFormatReader> reader = formatManager.createReaderFor(file);

    if (reader != 0) {
        int sampleCount = (int) reader->lengthInSamples;
        buffer->setSize(kNumSampleChannels, sampleCount, false, true, false);
        reader->read(buffer, 0, sampleCount, 0, true, true);
        if (reader->numChannels != kNumSampleChannels) {
            printf("File is mono, copying data to second channel\n");
            buffer->copyFrom(1, 0, *buffer, 0, 0, sampleCount);
        }
        return true;
    }

    return false;
}
