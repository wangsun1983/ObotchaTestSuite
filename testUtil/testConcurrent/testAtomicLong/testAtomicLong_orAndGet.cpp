#include <stdio.h>
#include <unistd.h>

#include "AtomicLong.hpp"
#include "Thread.hpp"
#include "TestLog.hpp"
using namespace obotcha;

void testOrAndGet() {
    while(1) {
      AtomicLong value = createAtomicLong(1);
      long v = value->orAndGet(2);
      if(v != 3) {
        TEST_FAIL("AtomicLong testOrAndGet test1");
        break;
      }
      break;
    }

    TEST_OK("AtomicLong testOrAndGet test100");
}
