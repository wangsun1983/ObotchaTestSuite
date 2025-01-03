#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "HashMap.hpp"
#include "Float.hpp"
#include "Float.hpp"
#include "TestLog.hpp"

using namespace obotcha;

void testHashMapAppend() {

    //void put(T t,U u)/get(T t)
    while(1) {
      HashMap<int,Integer> map = HashMap<int,Integer>::New();
      map->put(1,Integer::New(100));
      map->put(2,Integer::New(200));

      HashMap<int,Integer> map2 = HashMap<int,Integer>::New();
      map2->put(3,Integer::New(300));
      map2->put(4,Integer::New(400));

      map->append(map2);

      if(map->size() != 4) {
        TEST_FAIL("[HashMap Append case1]");
      }

      if(map->get(1)->toValue() != 100 || map->get(2)->toValue() != 200
        ||map->get(3)->toValue() != 300 || map->get(4)->toValue() != 400) {
        TEST_FAIL("[HashMap Append case2]");
      }
      break;
    }

    while(1) {
      HashMap<int,Integer> map = HashMap<int,Integer>::New();
      map->put(1,Integer::New(100));
      map->put(2,Integer::New(200));

      HashMap<int,Integer> map2 = HashMap<int,Integer>::New();
      map2->put(1,Integer::New(300));
      map2->put(2,Integer::New(400));

      map->append(map2);

      if(map->size() != 2) {
        TEST_FAIL("[HashMap Append case3]");
      }

      if(map->get(1)->toValue() != 100 || map->get(2)->toValue() != 200) {
        TEST_FAIL("[HashMap Append case4],v1 is %d,v2 is %d",map->get(1)->toValue(),map->get(2)->toValue());
      }
      break;
    }

    while(1) {
      HashMap<int,Integer> map = HashMap<int,Integer>::New();
      HashMap<int,Integer> map2 = HashMap<int,Integer>::New();
      map2->put(1,Integer::New(300));
      map2->put(2,Integer::New(400));

      map->append(map2);

      if(map->size() != 2) {
        TEST_FAIL("[HashMap Append case3]");
      }

      if(map->get(1)->toValue() != 300 || map->get(2)->toValue() != 400) {
        TEST_FAIL("[HashMap Append case5],v1 is %d,v2 is %d",map->get(1)->toValue(),map->get(2)->toValue());
      }
      break;
    }

    TEST_OK("[HashMap Append case100]");
}
