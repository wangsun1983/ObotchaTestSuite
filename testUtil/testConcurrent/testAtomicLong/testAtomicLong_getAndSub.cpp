#include <stdio.h>
#include <unistd.h>

#include "AtomicLong.hpp"
#include "Thread.hpp"

using namespace obotcha;

void testGetAndSub() {
    while(1) {
        for(int testLoop = 0;testLoop < 1024;testLoop++) {
            AtomicLong value = createAtomicLong(64*64*1024);
            ArrayList<Thread> list = createArrayList<Thread>();

            for(int i = 0;i < 32;i++) {
                Thread t = createThread([&value] {
                    for(int j = 0;j<64*1024;j++) {
                        value->getAndSub(2);
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
                printf("AtomicLong GetAndSub test1-------[FAILED],value is %ld \n",value->get());
                break;
            }
        }

        break;
    }

    while(1) {
      AtomicLong value = createAtomicLong(5);
      long v = value->getAndSub(2);
      if(v != 5) {
        printf("AtomicLong GetAndSub test2-------[FAILED],v is %ld \n",v);
        break;
      }

      if(value->get() != 3) {
        printf("AtomicLong GetAndSub test3-------[FAILED],v is %ld \n",value->get());
        break;
      }
      break;
    }

    printf("AtomicLong SubAndGet test100-------[OK] \n");
}