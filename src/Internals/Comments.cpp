// Copyright Benoit Blanchon 2014-2015
// MIT License
//
// Arduino JSON library
// https://github.com/bblanchon/ArduinoJson

#include "../../include/ArduinoJson/Internals/Comments.hpp"


inline static const char * ArduinoJson::Internals::skipCStyleComment(const char *ptr) {
  if(ptr) {
  ptr += 2;
  for (;;) {
    if (ptr[0] == '\0') return ptr;
    if (ptr[0] == '*' && ptr[1] == '/') return ptr + 2;
    ptr++;
  }
  } //if closed
  //Logic needs to be implemented
  
}

inline static const char * ArduinoJson::Internals::skipCppStyleComment(const char *ptr) {
  if(ptr){
  ptr += 2;
  for (;;) {
    if (ptr[0] == '\0' || ptr[0] == '\n') return ptr;
    ptr++;
  }
  } //if closed
//Logic needs to be implement
  
}

const char *ArduinoJson::Internals::skipSpacesAndComments(const char *ptr) {
  const char *ptrtoSkipSpaces = ptr;
  if(ptrtoSkipSpaces){
  for (;;) {
    switch (ptr[0]) {
      case ' ':
      case '\t':
      case '\r':
      case '\n':
        ptr++;
        return ptr;
      case '/':
        switch (ptr[1]) {
          case '*':
          const char* ptrtoCstyle = NULL;  
            ptrtoCstyle = ArduinoJson::Internals::skipCStyleComment(ptr);
            break;
          case '/':
          const char* ptrtoCppstyle = NULL;
            ptrtoCppstyle = ArduinoJson::Internals::skipCppStyleComment(ptr);
            break;
          default:
            return ptr;
        }
        break;
      default:
        return ptr;
    }
  }
  }// if closed
  //Logic needs to be implement
  
}
