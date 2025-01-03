#include <stdio.h>
#include <unistd.h>

#include "JsonWriter.hpp"
#include "JsonReader.hpp"
#include "TestLog.hpp"
#include "String.hpp"

using namespace obotcha;

int main() {

    //write a json
    JsonWriter writer = JsonWriter::New(String::New("./tmp/abc.json"));
    JsonValue value = JsonValue::New();
    value->put("a",1);
    value->put("c","nihao");

    JsonValue array = JsonValue::New();
    array->append("abc1");
    array->append("abc2");
    array->append("abc3");

    value->put("darr",array);

    writer->write(value);
    writer->close();

    //read a Json
    JsonReader reader = JsonReader::New()->loadFile(String::New("./tmp/abc.json"));
    JsonValue value2 = reader->get();
    while(1) {
      Integer i1 = value->getInteger("a");
      if(i1 == nullptr || i1->toValue() != 1) {
        TEST_FAIL("[JsonWriter Test {write()} case1]");
        break;
      }

      String s1 = value->getString("c");
      if(s1 == nullptr || !s1->sameAs("nihao")) {
        TEST_FAIL("[JsonWriter Test {write()} case2]");
        break;
      }

      JsonValue arr = value->getValue("darr");
      if(arr == nullptr) {
        TEST_FAIL("[JsonWriter Test {write()} case3]");
        break;
      }

      String ss1 = arr->getStringAt(0);
      if(ss1 == nullptr || !ss1->sameAs("abc1")) {
        TEST_FAIL("[JsonWriter Test {write()} case4]");
        break;
      }

      String ss2 = arr->getStringAt(1);
      if(ss2 == nullptr || !ss2->sameAs("abc2")) {
        TEST_FAIL("[JsonWriter Test {write()} case5]");
        break;
      }

      String ss3 = arr->getStringAt(2);
      if(ss3 == nullptr || !ss3->sameAs("abc3")) {
        TEST_FAIL("[JsonWriter Test {write()} case6]");
        break;
      }

      TEST_OK("[JsonWriter Test {write()} case7]");
      break;
    }


}
