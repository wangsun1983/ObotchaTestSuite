#include <stdio.h>
#include <unistd.h>

#include "AtomicUint8.hpp"
#include "Thread.hpp"
#include "TestLog.hpp"

using namespace obotcha;

void testGetAndDecrement() {
    while(1) {
        for(int testLoop = 0;testLoop < 16;testLoop++) {
            AtomicUint8 value = createAtomicUint8(8*8*2);
            ArrayList<Thread> list = createArrayList<Thread>();

            for(int i = 0;i < 8;i++) {
                Thread t = createThread([&value] {
                    for(int j = 0;j<8*2;j++) {
                        value->getAndDecrement();
                    }
                });
                list->add(t);
                t->start();
            }

            auto iterator = list->getIterator();
            while(iterator->hasValue()) {
               auto t = iterator->getValue();
               t->join();
               iterator->next();
            }

            if(value->get() != 0) {
                TEST_FAIL("AtomicUint8 GetAndDecrement test1");
                break;
            }
        }

        break;
    }

    while(1) {
      AtomicUint8 value = createAtomicUint8(5);
      long v = value->getAndDecrement();
      if(v != 5) {
        TEST_FAIL("AtomicUint8 GetAndDecrement test2");
        break;
      }

      if(value->get() != 4) {
        TEST_FAIL("AtomicUint8 GetAndDecrement test3");
        break;
      }
      break;
    }

    TEST_OK("AtomicUint8 GetAndDecrement test100");
}