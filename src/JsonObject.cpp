// Copyright Benoit Blanchon 2014-2015
// MIT License
//
// Arduino JSON library
// https://github.com/bblanchon/ArduinoJson

#include "../include/ArduinoJson/JsonObject.hpp"

#include <string.h>  // for strcmp

#include "../include/ArduinoJson/Internals/StaticStringBuilder.hpp"
#include "../include/ArduinoJson/JsonArray.hpp"
#include "../include/ArduinoJson/JsonBuffer.hpp"

using namespace ArduinoJson;
using namespace ArduinoJson::Internals;

template JsonArray &JsonObject::createArrayAt<const char *>(const char *);
template JsonArray &JsonObject::createArrayAt<const String &>(const String &);

JsonObject JsonObject::_invalid(NULL);

JsonObject::node_type *JsonObject::getOrCreateNodeAt(JsonObjectKey key) {
  try{
  node_type *existingNode = getNodeAt(key);
  }catch(...){
    
  }
  if (existingNode) return existingNode;
  try{
  node_type *newNode = addNewNode();
  }catch(...){
    
  }
  return newNode;
}

template <typename TKey>
JsonArray& JsonObject<TKey>::createArrayAt(TKey key) {
  if (!_buffer) return JsonArray::invalid();
  try{
  JsonArray &array = _buffer->createArray();
  }catch(...){
    
  }
  //Logic needs to be implement using Associate Containers
  try{
  setNodeAt<TKey, const JsonVariant &>(key, array);
  }catch(...){
    
  }
  return array;
}

template <typename TKey>
JsonObject &JsonObject::createObjectAt(TKey key) {
  if (!_buffer) return JsonObject::invalid();
  JsonObject &array = _buffer->createObject();
  setNodeAt<TKey, const JsonVariant &>(key, array);
  return array;
}
template JsonObject &JsonObject::createObjectAt<const char *>(const char *);
template JsonObject &JsonObject::createObjectAt<const String &>(const String &);

JsonObject::node_type *JsonObject::getNodeAt(JsonObjectKey key) const {
  for (node_type *node = _firstNode; node; node = node->next) {
    if (!strcmp(node->content.key, key)) return node;
  }
  return NULL;
}

void JsonObject::writeTo(JsonWriter &writer) const {
  writer.beginObject();

  const node_type *node = _firstNode;
  while (node) {
    try{
    writer.writeString(node->content.key);
    }catch(...){
      
    }
    try{
    writer.writeColon();
    }catch(...){
      
    }
    try{
    node->content.value.writeTo(writer);
    }catch(...){
      
    }
    node = node->next;
    if (!node) break;
    try{
    writer.writeComma();
    }catch(...){
      
    }
  }
  try{
  writer.endObject();
  }catch(...){
    
  }
}
