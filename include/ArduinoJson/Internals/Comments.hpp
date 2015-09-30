// Copyright Benoit Blanchon 2014-2015
// MIT License
//
// Arduino JSON library
// https://github.com/bblanchon/ArduinoJson

#pragma once

namespace ArduinoJson {
namespace Internals {
const char * skipSpacesAndComments(const char *ptr);
inline static const char * skipCStyleComment(const char *ptr);
inline static const char * skipCppStyleComment(const char *ptr);
}
}
