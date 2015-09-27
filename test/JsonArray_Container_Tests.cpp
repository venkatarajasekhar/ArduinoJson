// Copyright Benoit Blanchon 2014-2015
// MIT License
//
// Arduino JSON library
// https://github.com/bblanchon/ArduinoJson

#include <gtest/gtest.h>
#include <ArduinoJson.h>

class JsonArray_Container_Tests : public ::testing::Test {
 protected:
  JsonArray_Container_Tests() : _array(_jsonBuffer.createArray()) {}

  template <typename T>
  void firstMustEqual(T expected) {
    itemMustEqual(0, expected);
  }

  template <typename T>
  void secondMustEqual(T expected) {
    itemMustEqual(1, expected);
  }

  template <typename T>
  void firstMustReference(const T& expected) {
    itemMustReference(0, expected);
  }

  template <typename T>
  void secondMustReference(const T& expected) {
    itemMustReference(1, expected);
  }

  void sizeMustBe(int expected) { EXPECT_EQ(expected, _array.size()); }

  DynamicJsonBuffer _jsonBuffer;
  JsonArray& _array;

 private:
  template <typename T>
  void itemMustEqual(int index, T expected) {
    EXPECT_TRUE(_array[index].is<T>());
    EXPECT_EQ(expected, _array[index].as<T>());
  }

  template <typename T>
  void itemMustReference(int index, const T& expected) {
    EXPECT_TRUE(_array[index].is<T&>());
    EXPECT_EQ(&expected, &_array[index].as<T&>());
  }
};

template <>
void JsonArray_Container_Tests::itemMustEqual(int index, const char* expected) {
  EXPECT_STREQ(expected, _array[index].asString());
}

#define TEST_(name) TEST_F(JsonArray_Container_Tests, name)

TEST_(DontGrow_WhenValuesAreReplaced) {
  _array.add("hello");
  _array[0] = "world";
  sizeMustBe(1);
}

TEST_(CanSetToElementsFromArray) {
  JsonArray& arr = _jsonBuffer.createArray();
  arr.add(42);
  arr.add("hello");

  _array.add(0);
  _array.add(0);
  _array.set(0, arr[1]);
  _array.set(1, arr[0]);

  firstMustEqual("hello");
  secondMustEqual(42);
}

TEST_(CanSetToElementsFromObject) {
  JsonObject& obj = _jsonBuffer.createObject();
  obj["a"] = 42;
  obj["b"] = "hello";

  _array.add(0);
  _array.add(0);
  _array.set(0, obj["b"]);
  _array.set(1, obj["a"]);

  firstMustEqual("hello");
  secondMustEqual(42);
}

TEST_(CanAssignToElementsFromArray) {
  JsonArray& arr = _jsonBuffer.createArray();
  arr.add(42);
  arr.add("hello");

  _array.add(0);
  _array.add(0);
  _array[0] = arr[1];
  _array[1] = arr[0];

  firstMustEqual("hello");
  secondMustEqual(42);
}

TEST_(CanAssignElementsFromObject) {
  JsonObject& obj = _jsonBuffer.createObject();
  obj["a"] = 42;
  obj["b"] = "hello";

  _array.add(0);
  _array.add(0);
  _array[0] = obj["b"];
  _array[1] = obj["a"];

  firstMustEqual("hello");
  secondMustEqual(42);
}

TEST_(RemoveFirstElement) {
  _array.add("one");
  _array.add("two");
  _array.add("three");

  _array.removeAt(0);

  sizeMustBe(2);
  firstMustEqual("two");
  secondMustEqual("three");
}

TEST_(RemoveMiddleElement) {
  _array.add("one");
  _array.add("two");
  _array.add("three");

  _array.removeAt(1);

  sizeMustBe(2);
  firstMustEqual("one");
  secondMustEqual("three");
}

TEST_(RemoveLastElement) {
  _array.add("one");
  _array.add("two");
  _array.add("three");

  _array.removeAt(2);

  sizeMustBe(2);
  firstMustEqual("one");
  secondMustEqual("two");
}
