#pragma once

#include "JsonContainer.h"

class JsonArray;
class JsonValue;
struct JsonNode;

class JsonObject : public JsonContainer
{
public:

    JsonObject()
    {
    }

    explicit JsonObject(JsonNode* node)
        : JsonContainer(node)
    {
    }

    JsonValue operator[](const char* key);
    void remove(const char* key);

    JsonArray createNestedArray(const char* key);
    JsonObject createNestedObject(const char* key);

private:
    JsonNode* getOrCreateNodeAt(const char* key);
    JsonNode* createContainerNodeAt(const char* key, JsonNodeType type);
};