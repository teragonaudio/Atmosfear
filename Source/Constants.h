/*
  ==============================================================================

    Constants.h
    Created: 9 May 2015 1:17:51pm
    Author:  nik

  ==============================================================================
*/

#ifndef CONSTANTS_H_INCLUDED
#define CONSTANTS_H_INCLUDED

#include <string>

static const int kMaxVoiceCount = 8;
static const int kNumSampleChannels = 2;
static const int kMaxRandomizePercentage = 25;

static const double kMinPeriodInSec = 0.001;
static const double kMaxPeriodInSec = 60.0;
static const double kDefaultPeriodInSec = 1.0;

static const int kMaxRandomness = 100;
static const int kDefaultRandomness = 50;

static const double kMinVoiceVolume = -60.0;
static const double kMaxVoiceVolume = 0.0;
static const double kDefaultVoiceVolume = -4.0;

extern const std::string kDatabasePath;
extern const std::string kDirPrefix;

std::string getVoiceParamName(const char *paramName, size_t index);

#endif  // CONSTANTS_H_INCLUDED
