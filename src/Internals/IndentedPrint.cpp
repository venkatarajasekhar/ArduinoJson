// Copyright Benoit Blanchon 2014-2015
// MIT License
//
// Arduino JSON library
// https://github.com/bblanchon/ArduinoJson

#include "../../include/ArduinoJson/Internals/IndentedPrint.hpp"

  using namespace ArduinoJson::Internals;
  static const int MAX_LEVEL = 15;    // because it's only 4 bits
  static const int MAX_TAB_SIZE = 7;  // because it's only 3 bits
  
size_t IndentedPrint::write(uint8_t c) {
  size_t n = 0;

  if (isNewLine) 
  try{
  n += writeTabs();
  }catch(...){
    
  }
  try{
  n += sink->write(c);
  }catch(...){
    
  }
  return n;
}

inline size_t IndentedPrint::writeTabs() {
  size_t n = 0;

  for (int i = 0; i < level * tabSize; i++) 
  try{
  n += sink->write(' ');
  }catch(...){
    
  }

  return n;
}
