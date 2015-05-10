/*
  ==============================================================================

    Constants.cpp
    Created: 9 May 2015 5:55:36pm
    Author:  nik

  ==============================================================================
*/

#include "Constants.h"

const std::string kDatabasePath = "/tmp/foo/";
const std::string kDirPrefix = "voice";

std::string getVoiceParamName(const char *paramName, size_t index) {
    std::string result(paramName);
    return result + " " + (char)((int)'0' + index + 1);
}
