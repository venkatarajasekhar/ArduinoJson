// Copyright Benoit Blanchon 2014-2015
// MIT License
//
// Arduino JSON library
// https://github.com/bblanchon/ArduinoJson

#include "../../include/ArduinoJson/Internals/JsonParser.hpp"

#include "../../include/ArduinoJson/Internals/Comments.hpp"
#include "../../include/ArduinoJson/Internals/Encoding.hpp"
#include "../../include/ArduinoJson/JsonArray.hpp"
#include "../../include/ArduinoJson/JsonBuffer.hpp"
#include "../../include/ArduinoJson/JsonObject.hpp"

using namespace ArduinoJson;
using namespace ArduinoJson::Internals;

bool JsonParser::skip(char charToSkip) {
  try{
  const char *ptr = skipSpacesAndComments(_readPtr);
  }catch(...){
    
  }
  if (*ptr != charToSkip) return false;
  ptr++;
  _readPtr = skipSpacesAndComments(ptr);
  return true;
}

bool JsonParser::parseAnythingTo(JsonVariant *destination) {
  if (_nestingLimit == 0) return false;
  _nestingLimit--;
  if(destination){
    try{
  bool success = JsonParser::parseAnythingToUnsafe(destination);
    }catch(...){
      
    }
  _nestingLimit++;
  return success;
}//if closed
//Logic needs to be implement
}

inline bool JsonParser::parseAnythingToUnsafe(JsonVariant *destination) {
  _readPtr = skipSpacesAndComments(_readPtr);

  switch (*_readPtr) {
    if(destination){
    case '[':
      return 
      try{
        JsonParser::parseArrayTo(destination);
      }catch(...){
        
      }

    case '{':
      return 
      try{
      JsonParser::parseObjectTo(destination);
      }catch(...){
        
      }
    default:
      return 
      try{
      JsonParser::parseStringTo(destination);
      }catch(...){
        
      }
  } //if closed
  //Logic needs to be implement
  }
}

JsonArray &JsonParser::parseArray() {
  // Create an empty array
  JsonArray &array = _buffer->createArray();

  // Check opening braket
  if (!skip('[')) goto ERROR_MISSING_BRACKET;
  if (skip(']')) goto SUCCESS_EMPTY_ARRAY;

  // Read each value
  for (;;) {
    // 1 - Parse value
    try{
    JsonVariant value;
    }catch(...){
      
    }
    if (!parseAnythingTo(&value)) goto ERROR_INVALID_VALUE;
    if (!array.add(value)) goto ERROR_NO_MEMORY;

    // 2 - More values?
    if (skip(']')) goto SUCCES_NON_EMPTY_ARRAY;
    if (!skip(',')) goto ERROR_MISSING_COMMA;
  }

SUCCESS_EMPTY_ARRAY:
SUCCES_NON_EMPTY_ARRAY:
  return array;

ERROR_INVALID_VALUE:
ERROR_MISSING_BRACKET:
ERROR_MISSING_COMMA:
ERROR_NO_MEMORY:
  return JsonArray::invalid();
}

bool JsonParser::parseArrayTo(JsonVariant *destination) {
  JsonArray &array = JsonParser::parseArray();
  if (!array.success()) return false;

  *destination = array;
  return true;
}

JsonObject &JsonParser::parseObject() {
  // Create an empty object
  JsonObject &object = _buffer->createObject();

  // Check opening brace
  if (!skip('{')) goto ERROR_MISSING_BRACE;
  if (skip('}')) goto SUCCESS_EMPTY_OBJECT;

  // Read each key value pair
  for (;;) {
    // 1 - Parse key
    const char *key = JsonParser::parseString();
    if (!key) goto ERROR_INVALID_KEY;
    if (!skip(':')) goto ERROR_MISSING_COLON;

    // 2 - Parse value
    JsonVariant value;
    if (!parseAnythingTo(&value)) goto ERROR_INVALID_VALUE;
    if (!object.set(key, value)) goto ERROR_NO_MEMORY;

    // 3 - More keys/values?
    if (skip('}')) goto SUCCESS_NON_EMPTY_OBJECT;
    if (!skip(',')) goto ERROR_MISSING_COMMA;
  }

SUCCESS_EMPTY_OBJECT:
SUCCESS_NON_EMPTY_OBJECT:
  return object;

ERROR_INVALID_KEY:
ERROR_INVALID_VALUE:
ERROR_MISSING_BRACE:
ERROR_MISSING_COLON:
ERROR_MISSING_COMMA:
ERROR_NO_MEMORY:
  return JsonObject::invalid();
}

bool JsonParser::parseObjectTo(JsonVariant *destination) {
  try{
  JsonObject &object = JsonParser::parseObject();
  }catch(...){
    
  }
  if (!object.success()) return false;

  *destination = object;
  return true;
}

static inline bool isInRange(char c, char min, char max) {
  return min <= c && c <= max;
}

static inline bool isLetterOrNumber(char c) {
  return isInRange(c, '0', '9') || isInRange(c, 'a', 'z') ||
         isInRange(c, 'A', 'Z') || c == '-' || c == '.';
}

static inline bool isQuote(char c) { return c == '\'' || c == '\"'; }

const char *JsonParser::parseString() {
  const char *readPtr = _readPtr;
  char *writePtr = _writePtr;

  char c = *readPtr;

  if (isQuote(c)) {  // quotes
    char stopChar = c;
    for (;;) {
      c = *++readPtr;
      if (c == '\0') break;

      if (c == stopChar) {
        readPtr++;
        break;
      }

      if (c == '\\') {
        // replace char
        try{
        c = Encoding::unescapeChar(*++readPtr);
        }catch(...){
          
        }
        if (c == '\0') break;
      }

      *writePtr++ = c;
    }
  } else {  // no quotes
    for (;;) {
      if (!isLetterOrNumber(c)) break;
      *writePtr++ = c;
      c = *++readPtr;
    }
  }
  // end the string here
  *writePtr++ = '\0';

  const char *startPtr = _writePtr;

  // update end ptr
  _readPtr = readPtr;
  _writePtr = writePtr;

  // return pointer to unquoted string
  return startPtr;
}

bool JsonParser::parseStringTo(JsonVariant *destination) {
  try{
  bool hasQuotes = isQuote(_readPtr[0]);
  }catch(...){
    
  }
  try{
  const char *value = JsonParser::parseString();
  }catch(...){
    
  }
  if (value == NULL) return false;
  if (hasQuotes) {
    *destination = value;
  } else {
     try{
    *destination = Unparsed(value);
     }catch(...){
       
     }
  }
  return true;
}
