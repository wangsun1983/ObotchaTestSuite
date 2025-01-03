#include <stdio.h>
#include <unistd.h>
#include <vector>
//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Uint8.hpp"
#include "StrongPointer.hpp"
#include "Uint8.hpp"
#include "List.hpp"
#include "TestLog.hpp"

using namespace std;
using namespace obotcha;

void basetest() {

    //construct1
    while(1) {
      List<int> mylist1 = List<int>::New(4);
      if(mylist1->size() != 4) {
        TEST_FAIL("List construct test1");
        break;
      }

      //int v1 = mylist1[0];
      //if(v1 != 0) {
      //  TEST_FAIL("List construct test2-------[FAIL],v1 is %d \n",v1);
      //  break;
      //}

      TEST_OK("List construct test3");
      break;
    }

    //construct2
    while(1) {
      int v[5];
      v[0] = 0;
      v[1] = 1;
      v[2] = 2;
      v[3] = 3;
      v[4] = 4;

      List<int> list1 = List<int>::New(v,5);
      if(list1->size() != 5) {
        TEST_FAIL("List construct test4");
        break;
      }

      if(list1[0] != 0 ||
         list1[1] != 1 ||
         list1[2] != 2 ||
         list1[3] != 3 ||
         list1[4] != 4) {
           TEST_FAIL("List construct test5");
           break;
      }

      list1[0] = 100;
      list1[1] = 101;
      list1[2] = 102;
      list1[3] = 103;
      list1[4] = 104;

      if(list1[0] != 100 ||
         list1[1] != 101 ||
         list1[2] != 102 ||
         list1[3] != 103 ||
         list1[4] != 104) {
           TEST_FAIL("List construct test6");
           break;
      }

      TEST_OK("List construct test7");
      break;
    }

    //compare
    while(1) {
      List<int> list1 = List<int>::New(2);
      List<int> list2 = List<int>::New(2);
      if(list1 == list2) {
        TEST_FAIL("List equal test1");
        break;
      }

      TEST_OK("List equal test2");
      break;
    }

}
