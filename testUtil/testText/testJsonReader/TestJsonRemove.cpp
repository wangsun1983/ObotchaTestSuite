#include <stdio.h>
#include <unistd.h>

#include "JsonWriter.hpp"
#include "JsonReader.hpp"
#include "JsonValue.hpp"
#include "File.hpp"

#include "Log.hpp"
#include "TestLog.hpp"


using namespace obotcha;

int testremove() {
    JsonReader mReader = createJsonReader(createFile("abc.json"));
    JsonValue root = mReader->get();

    JsonValue arr = root->getValue("arr");
    arr->removeAt(1);
    if(arr->size() != 2) {
      TEST_FAIL("[JsonReader testRemove case1,size is %d ]",arr->size());
    }

    String attr1 = arr->getStringAt(0);
    if(!attr1->equals("abc1")) {
      TEST_FAIL("[JsonReader testRemove case2]");
    }

    String attr2 = arr->getStringAt(1);
    if(!attr2->equals("abc3")) {
      TEST_FAIL("[JsonReader testRemove case3]");
    }

    TEST_OK("[JsonReader testRemove case]");
    return 0;
}
