#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "ConcurrentStack.hpp"
#include "String.hpp"
#include "TestLog.hpp"
#include "TimeWatcher.hpp"


using namespace obotcha;

void testConcurrentStack_Clear() {
    while(1) {
      ConcurrentStack<String> list = createConcurrentStack<String>();
      Thread t1 = createThread([&]{
          list->syncReadAction([]{
             usleep(1000*200); 
          });
      });
      
      Thread t2 = createThread([&]{
          usleep(1000*100);
          TimeWatcher watcher = createTimeWatcher();
          watcher->start();
          list->clear();
          auto ret = watcher->stop();
          if(ret < 95 || ret > 105) {
            TEST_FAIL("ConcurrentStack clear case1,ret is %d",ret);
          }
      });
      
      t1->start();
      t2->start();
      
      t1->join();
      t2->join();
      
      if(list->size() != 0) {
          TEST_FAIL("ConcurrentStack clear case2");
      }
      break;
    }
    
    while(1) {
      ConcurrentStack<String> list = createConcurrentStack<String>();
      Thread t1 = createThread([&]{
          list->syncWriteAction([]{
             usleep(1000*200); 
          });
      });
      
      Thread t2 = createThread([&]{
          usleep(1000*100);
          TimeWatcher watcher = createTimeWatcher();
          watcher->start();
          list->clear();
          auto ret = watcher->stop();
          if(ret < 95 || ret > 105) {
            TEST_FAIL("ConcurrentStack clear case3,ret is %d",ret);
          }
      });
      
      t1->start();
      t2->start();
      
      t1->join();
      t2->join();
      
      if(list->size() != 0) {
          TEST_FAIL("ConcurrentStack clear case4");
      }
      break;
    }

    TEST_OK("ConcurrentStack clear case100");
}