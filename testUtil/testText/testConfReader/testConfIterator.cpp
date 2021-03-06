#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "HashMap.hpp"
#include "ConfReader.hpp"
#include "Log.hpp"
#include "TestLog.hpp"

using namespace obotcha;

void testConfIterator() {
    ConfReader reader = createConfReader("simple.conf");
    //ConfIterator(String);
    while(1) {
      ConfIterator iterator = reader->getIterator();
      HashMap<String,String> mHashMap = createHashMap<String,String>();
      while(iterator->hasValue()) {
          mHashMap->put(iterator->getTag(),iterator->getValue());
          iterator->next();
      }

      if(mHashMap->size() != 4) {
          TEST_FAIL("[ConfIterator Test {getValue()/next()} case1],mHashMap size is %d ",mHashMap->size());
          break;
      }

      String v1 = mHashMap->get(createString("Desktop-Picture"));
      if(!v1->equals("/usr/images/earth.jpg")) {
        TEST_FAIL("[ConfIterator Test {getValue()/next()} case2] ");
        break;
      }

      String v2 = mHashMap->get(createString("Position"));
      if(!v2->equals("Centered")) {
        TEST_FAIL("[ConfIterator Test {getValue()/next()} case3] ");
        break;
      }

      String v3 = mHashMap->get(createString("Background Color"));
      if(!v3->equals("Black")) {
        TEST_FAIL("[ConfIterator Test {getValue()/next()} case4] ");
        break;
      }

      String v4 = mHashMap->get(createString("NULL"));
      if(v4->size() != 0) {
        TEST_FAIL("[ConfIterator Test {getValue()/next()} case5] ");
        break;
      }

      TEST_OK("[ConfIterator Test {getValue()/next()} case100]");
      break;
    }

}
