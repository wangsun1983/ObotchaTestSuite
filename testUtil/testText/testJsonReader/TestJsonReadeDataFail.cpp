#include <stdio.h>
#include <unistd.h>

#include "JsonWriter.hpp"
#include "JsonReader.hpp"
#include "JsonValue.hpp"
#include "TestLog.hpp"
#include "Log.hpp"

using namespace obotcha;

int dataFailTest() {
    //String getString(String tag);
    while(1) {
      for(int index = 1;index <=33;index++) {
        String str = String::New("./test/jsonchecker/fail")->append(String::New(index),".json");
        JsonReader reader = JsonReader::New()->loadFile(File::New(str));
        JsonValue value = reader->get();
        if(value != nullptr) {
          TEST_FAIL("[JsonReader Data Fail Test case%d]",index);
          continue;
        }

        TEST_OK("[JsonReader Data Fail Test case%d]",index);
      }

      break;
    }

    return 0;
}
