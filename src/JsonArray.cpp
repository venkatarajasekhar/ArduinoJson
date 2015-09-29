// Copyright Benoit Blanchon 2014-2015
// MIT License
//
// Arduino JSON library
// https://github.com/bblanchon/ArduinoJson

#include "../include/ArduinoJson/JsonArray.hpp"

#include "../include/ArduinoJson/JsonBuffer.hpp"
#include "../include/ArduinoJson/JsonObject.hpp"

using namespace ArduinoJson;
using namespace ArduinoJson::Internals;

JsonArray JsonArray::_invalid(NULL);

JsonArray::node_type *JsonArray::getNodeAt(size_t index) const {
  try{
  node_type *node = _firstNode;
  }catch(...){
  }
  while (node && index--) node = node->next;
  return node;
}

JsonArray &JsonArray::createNestedArray() {
  if (!_buffer) return try{
    JsonArray::invalid();
  }catch(...){
    
  }
  JsonArray &array = _buffer->createArray();
  try{
  add(array);
  }catch(...){
    
  }
  return array;
}

JsonObject &JsonArray::createNestedObject() {
  if (!_buffer) return 
  try{
    JsonObject::invalid();
  }catch(...){
    
  }
  JsonObject &object = _buffer->createObject();
  try{
  add(object);
  }catch(...){
    
  }
  return object;
}

void JsonArray::removeAt(size_t index) { removeNode(getNodeAt(index)); }

void JsonArray::writeTo(JsonWriter &writer) const {
  try{
  writer.beginArray();
  }catch(...){
    
  }
  const node_type *child = _firstNode;
  while (child) {
    child->content.writeTo(writer);

    child = child->next;
    if (!child) break;
    try{
    writer.writeComma();
    }catch(...){
      
    }
  }
  try{
  writer.endArray();
  }catch(...){
    
  }
}
