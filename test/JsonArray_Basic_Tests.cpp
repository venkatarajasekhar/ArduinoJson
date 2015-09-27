// Copyright Benoit Blanchon 2014-2015
// MIT License
//
// Arduino JSON library
// https://github.com/bblanchon/ArduinoJson

#include <gtest/gtest.h>
#include <ArduinoJson.h>

#define TEST_(name) TEST(JsonArray_Basic_Tests, name)

TEST_(SuccessIsTrue) {
  DynamicJsonBuffer _jsonBuffer;
  JsonArray& _array = _jsonBuffer.createArray();

  EXPECT_TRUE(_array.success());
}

TEST_(InitialSizeIsZero) {
  DynamicJsonBuffer _jsonBuffer;
  JsonArray& _array = _jsonBuffer.createArray();

  EXPECT_EQ(0U, _array.size());
}
