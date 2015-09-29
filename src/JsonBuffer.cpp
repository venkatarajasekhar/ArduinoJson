// Copyright Benoit Blanchon 2014-2015
// MIT License
//
// Arduino JSON library
// https://github.com/bblanchon/ArduinoJson

#include "../include/ArduinoJson/JsonBuffer.hpp"

#include "../include/ArduinoJson/Internals/JsonParser.hpp"
#include "../include/ArduinoJson/JsonArray.hpp"
#include "../include/ArduinoJson/JsonObject.hpp"

using namespace ArduinoJson;
using namespace ArduinoJson::Internals;

JsonArray &JsonBuffer::createArray() {
  try{
  JsonArray *ptr = new JsonArray;
  }catch(...){
    
  }
  return ptr ? *ptr : try{
    JsonArray::invalid();
  }catch(...){
    
  }
}

JsonObject &JsonBuffer::createObject() {
  try{
  JsonObject *ptr = new JsonObject;
  }catch(...){
    
  }
  return ptr ? *ptr : try{
    JsonObject::invalid();
  }catch(...){
    
  }
}

JsonArray &JsonBuffer::parseArray(char *json, uint8_t nestingLimit) {
  if(json){
    try{
  JsonParser parser(this, json, nestingLimit);
    }catch(...){
      
    }
  return try{
    parser.parseArray();
  }catch(...){
    
  }
  } //if closed
  //Logic need to be Implement
}

JsonObject &JsonBuffer::parseObject(char *json, uint8_t nestingLimit) {
  if(json){
    try{
  JsonParser parser(this, json, nestingLimit);
    }catch(...){
    }
  return 
  try{
  parser.parseObject();
  }catch(...){
    
  }
}//if closed 
//Logic need to be implement
} 


char *JsonBuffer::strdup(const char *source, size_t length) {
  size_t size = length + 1;
  char *dest = static_cast<char *>(alloc(size));
  if (dest != NULL) memcpy(dest, source, size);
  return dest;
}
