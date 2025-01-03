#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "HttpMime.hpp"
#include "Math.hpp"
#include "HttpUrlEncodedValue.hpp"
#include "TestLog.hpp"

using namespace obotcha;

void testUrlEncodedValueParse() {
  while(1) {
    HttpUrlEncodedValue v = HttpUrlEncodedValue::New("abc=1&bbb=qq&ccc=ffds");
    auto map = v->getValues();
    //KeyValuePair<String,String> l0 = list->get(0);
    //if(!l0->getKey()->sameAs("abc")) {
    //  TEST_FAIL("[HttpUrlEncodedValue test Parse case1]");
    //  break;
    //}

    if(!map->get("abc")->sameAs("1")) {
      TEST_FAIL("[HttpUrlEncodedValue test Parse case2]");
      break;
    }

    //KeyValuePair<String,String> l1 = list->get(1);
    //if(!l1->getKey()->sameAs("bbb")) {
    //  TEST_FAIL("[HttpUrlEncodedValue test Parse case3]");
    //  break;
    //}

    if(!map->get("bbb")->sameAs("qq")) {
      TEST_FAIL("[HttpUrlEncodedValue test Parse case4]");
      break;
    }

    //KeyValuePair<String,String> l2 = list->get(2);
    //if(!l2->getKey()->sameAs("ccc")) {
    //  TEST_FAIL("[HttpUrlEncodedValue test Parse case3]");
    //  break;
    //}

    if(!map->get("ccc")->sameAs("ffds")) {
      TEST_FAIL("[HttpUrlEncodedValue test Parse case5]");
      break;
    }

    break;
  }

  TEST_OK("[HttpUrlEncodedValue test Parse case100]");

}
