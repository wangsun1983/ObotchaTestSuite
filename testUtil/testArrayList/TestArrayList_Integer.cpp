#include <iostream>
#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "ArrayList.hpp"
#include "Integer.hpp"
#include "String.hpp"
#include "TestLog.hpp"

using namespace obotcha;

void testArrayList_Integer() {
  //--[_ArrayList<Integer> Test {add(Integer val)} Start]
  while(1) {
    ArrayList<Integer>list = ArrayList<Integer>::New();
    list->add(Integer::New(1));
    list->add(Integer::New(2));

    if(list->size() != 2) {
      TEST_FAIL("[ArrayList<Integer> Test {add(Integer val)} case0]");
      break;
    }

    if(list->get(0)->toValue() != 1
    ||list->get(1)->toValue() != 2) {
      TEST_FAIL("[ArrayList<Integer> Test {add(Integer val)} case1]");
      break;
    }

    Integer t;
    int size = list->size();
    list->add(t);
    if(size == list->size()) {
      TEST_FAIL("[ArrayList<Integer> Test {add(Integer val)} case2]");
      break;
    }

    TEST_OK("[ArrayList<Integer> Test {add(Integer val)}]");
    break;
  }

  //--[_ArrayList<Integer> Test {add(int val)} Start]
  while(1) {
    ArrayList<Integer>list = ArrayList<Integer>::New();
    list->add(Integer::New(1));
    list->add(Integer::New(2));

    if(list->size() != 2) {
      TEST_FAIL("[ArrayList<Integer> Test {add(int val)} case0]");
      break;
    }

    if(list->get(0)->toValue() != 1
    ||list->get(1)->toValue() != 2) {
      TEST_FAIL("[ArrayList<Integer> Test {add(int val)} case1]");
      break;
    }

    TEST_OK("[ArrayList<Integer> Test {add(int val)}]");
    break;
  }

  //--[_ArrayList<Integer> Test {add(ArrayList<Integer> list)} Start]
  while(1) {
    ArrayList<Integer>list = ArrayList<Integer>::New();
    list->add(Integer::New(1));
    list->add(Integer::New(2));

    ArrayList<Integer>list2 = ArrayList<Integer>::New();
    list2->add(Integer::New(3));
    list2->add(Integer::New(4));
    list->add(list2);

    if(list->size() != 4) {
      TEST_FAIL("[ArrayList<Integer> Test {add(ArrayList<Integer> list)} case0]");
      break;
    }

    if(list->get(0)->toValue() != 1
    ||list->get(1)->toValue() != 2
    ||list->get(2)->toValue() != 3
    ||list->get(3)->toValue() != 4) {
      TEST_FAIL("[ArrayList<Integer> Test {add(ArrayList<Integer> list)} case1]");
      break;
    }
/*
    ArrayList<Integer>list3;
    int size = list->size();
    list->add(list3);
    if(size != list->size()) {
      TEST_FAIL("[ArrayList<Integer> Test {add(ArrayList<Integer> list)} case2]");
      break;
    }
*/
    TEST_OK("[ArrayList<Integer> Test {add(ArrayList<Integer> val)}]");
    break;
  }
  //--[_ArrayList<Integer> Test {clear()} Start]
  while(1) {
    ArrayList<Integer>list = ArrayList<Integer>::New();
    list->add(Integer::New(1));
    list->add(Integer::New(2));
    int size = list->size();
    list->clear();
    if(size == 0 || list->size() != 0) {
      TEST_FAIL("[ArrayList<Integer> Test {clear()} case0]");
      break;
    }

    TEST_OK("[ArrayList<Integer> Test {clear()}]");
    break;
  }
  //--[_ArrayList<Integer> Test {remove(int index)} Start]
  while(1) {
    ArrayList<Integer>list = ArrayList<Integer>::New();
    list->add(Integer::New(1));
    list->add(Integer::New(2));
    list->add(Integer::New(3));

    Integer i = list->removeAt(2);
    if(i->toValue() != 3) {
      TEST_FAIL("[ArrayList<Integer> Test {remove(int index)} case0]");
      break;
    }

    if(list->size() != 2) {
      TEST_FAIL("[ArrayList<Integer> Test {remove(int index)} case1]");
      break;
    }

    bool isException = false;
    try {
         Integer i2 = list->removeAt(100);
    } catch(ArrayIndexOutOfBoundsException e) {
         isException = true;
    }

    if(!isException) {
      TEST_FAIL("[ArrayList<Integer> Test {remove(int index)} case2]");
      break;
    }

    isException = false;
    try {
        Integer i3 = list->removeAt(-1);
    } catch(ArrayIndexOutOfBoundsException e) {
         isException = true;
    }

    if(!isException) {
      TEST_FAIL("[ArrayList<Integer> Test {remove(int index)} case3]");
      break;
    }

    TEST_OK("[ArrayList<Integer> Test {remove(int index)}]");
    break;
  }

  //--[_ArrayList<Integer> Test {remove(Integer v)} Start]
  while(1) {
    ArrayList<Integer>list = ArrayList<Integer>::New();
    list->add(Integer::New(1));
    list->add(Integer::New(2));
    list->add(Integer::New(3));

    int result = list->remove(Integer::New(2));
    if(result == -1) {
      TEST_FAIL("[ArrayList<Integer> Test {remove(Integer v)} case0]");
      break;
    }

    if(list->size() != 2
      ||list->get(0)->toValue() != 1
      ||list->get(1)->toValue() != 3){
        TEST_FAIL("[ArrayList<Integer> Test {remove(Integer v)} case1]");
        break;
    }

    Integer t1 = Integer::New(100);
    if(list->remove(t1) != -1) {
      TEST_FAIL("[ArrayList<Integer> Test {remove(Integer v)} case2]");
      break;
    }

    Integer t2;
    int size = list->size();
    if(list->remove(t2) != -1) {
      TEST_FAIL("[ArrayList<Integer> Test {remove(Integer v)} case3]");
      break;
    }

    if(size != list->size()) {
      TEST_FAIL("[ArrayList<Integer> Test {remove(Integer v)} case4]");
      break;
    }

    TEST_OK("[ArrayList<Integer> Test {remove(Integer v)}]");
    break;
  }

  //--[_ArrayList<Integer> Test {indexOf(Integer v)} Start]
  while(1) {
    ArrayList<Integer>list = ArrayList<Integer>::New();
    list->add(Integer::New(1));
    list->add(Integer::New(2));
    list->add(Integer::New(3));

    if(list->indexOf(Integer::New(1)) != 0
      ||list->indexOf(Integer::New(2)) != 1
      ||list->indexOf(Integer::New(3)) != 2) {
        TEST_FAIL("[ArrayList<Integer> Test {indexOf(Integer v)} case0]");
        break;
    }

    if(list->indexOf(Integer::New(100)) != -1) {
      TEST_FAIL("[ArrayList<Integer> Test {indexOf(Integer v)} case1]");
      break;
    }

    Integer p;
    if(list->indexOf(p) != -1) {
      TEST_FAIL("[ArrayList<Integer> Test {indexOf(Integer v)} case1]");
      break;
    }

    TEST_OK("[ArrayList<Integer> Test {indexOf(Integer v)}]");
    break;
  }

  //--[_ArrayList<Integer> Test {set(int index,Integer val)} Start]
  while(1) {
    ArrayList<Integer>list = ArrayList<Integer>::New();
    list->add(Integer::New(1));
    list->add(Integer::New(2));
    list->add(Integer::New(3));

    list->set(0,Integer::New(2));
    if(list->get(0)->toValue() != 2
    ||list->get(1)->toValue() != 2
    ||list->get(2)->toValue() != 3) {
      TEST_FAIL("[ArrayList<Integer> Test {set(int index,Integer val)} case1]");
      break;
    }

    Integer t1;
    int result = list->set(1,t1);
    if(result != 0) {
      TEST_FAIL("[ArrayList<Integer> Test {set(int index,Integer val)} case2]");
      break;
    }

    if(list->get(1) != nullptr) {
      TEST_FAIL("[ArrayList<Integer> Test {set(int index,Integer val)} case2_1]");
      break;
    }

    bool isException = false;
    try {
        result = list->set(100,Integer::New(1));
    } catch(ArrayIndexOutOfBoundsException e) {
        isException = true;
    }

    if(!isException) {
      TEST_FAIL("[ArrayList<Integer> Test {set(int index,Integer val)} case3]");
      break;
    }

    if(list->get(0)->toValue() != 2
    ||list->get(2)->toValue() != 3) {
      TEST_FAIL("[ArrayList<Integer> Test {set(int index,Integer val)} case4]");
      break;
    }

    if(list->size() != 3) {
      TEST_FAIL("[ArrayList<Integer> Test {set(int index,Integer val)} case5]");
      break;
    }

    TEST_OK("[ArrayList<Integer> Test {set(int index,Integer val)}]");
    break;
  }

  //--[_ArrayList<Integer> Test {set(int index,int val)} Start]
  while(1) {
    ArrayList<Integer>list = ArrayList<Integer>::New();
    list->add(Integer::New(1));
    list->add(Integer::New(2));
    list->add(Integer::New(3));

    list->set(0,Integer::New(2));
    if(list->get(0)->toValue() != 2
    ||list->get(1)->toValue() != 2
    ||list->get(2)->toValue() != 3) {
      TEST_FAIL("[ArrayList<Integer> Test {set(int index,int val)} case1]");
      break;
    }

    Integer t1;
    int result = list->set(1,t1);
    if(result != 0) {
      TEST_FAIL("[ArrayList<Integer> Test {set(int index,int val)} case2]");
      break;
    }

    if(list->get(1) != nullptr){
      TEST_FAIL("[ArrayList<Integer> Test {set(int index,int val)} case2_1]");
      break;
    }

    bool isException = false;
    try {
        result = list->set(100,Integer::New(1));
    } catch(ArrayIndexOutOfBoundsException e) {
       isException = true;
    }

    if(!isException) {
      TEST_FAIL("[ArrayList<Integer> Test {set(int index,int val)} case3]");
      break;
    }

    if(list->get(0)->toValue() != 2
    ||list->get(2)->toValue() != 3) {
      TEST_FAIL("[ArrayList<Integer> Test {set(int index,int val)} case4]");
      break;
    }

    if(list->size() != 3) {
      TEST_FAIL("[ArrayList<Integer> Test {set(int index,int val)} case5]");
      break;
    }

    TEST_OK("[ArrayList<Integer> Test {set(int index,int val)}]");
    break;
  }

  //--[_ArrayList<Integer> Test {get(int index)} Start]
  while(1) {
    ArrayList<Integer>list = ArrayList<Integer>::New();
    list->add(Integer::New(1));
    list->add(Integer::New(2));
    list->add(Integer::New(3));

    Integer v1 = list->get(1);
    if(v1->toValue() != 2) {
      TEST_FAIL("[ArrayList<Integer> Test {get(int index)} case0]");
      break;
    }

    bool isException = false;
    try {
        Integer v2 = list->get(1000);
    } catch(ArrayIndexOutOfBoundsException e) {
       isException = true;
    }

    if(!isException) {
      TEST_FAIL("[ArrayList<Integer> Test {get(int index)} case1]");
      break;
    }

    isException = false;
    try {
        Integer v3 = list->get(-1);
    } catch(ArrayIndexOutOfBoundsException e) {
       isException = true;
    }

    if(!isException) {
      TEST_FAIL("[ArrayList<Integer> Test {get(int index)} case2]");
      break;
    }

    TEST_OK("[ArrayList<Integer> Test {get(int index)}]");
    break;
  }

  //--[_ArrayList<Integer> Test {insert(int index,Integer val)} Start]
  while(1) {
    ArrayList<Integer>list = ArrayList<Integer>::New();
    list->add(Integer::New(1));
    list->add(Integer::New(2));
    list->add(Integer::New(3));

    list->insert(1,Integer::New(4));
    if(list->get(0)->toValue() != 1
    ||list->get(1)->toValue() != 4
    ||list->get(2)->toValue() != 2
    ||list->get(3)->toValue() != 3) {
      TEST_FAIL("[ArrayList<Integer> Test {insert(int index,Integer val)} case0]");
      break;
    }

    int size = list->size();
    bool isException = false;
    try {
        int result = list->insert(100,Integer::New(4));
    } catch(ArrayIndexOutOfBoundsException e) {
        isException = true;
    }

    if(!isException) {
      TEST_FAIL("[ArrayList<Integer> Test {insert(int index,Integer val)} case1]");
      break;
    }

    isException = false;
    try {
        list->insert(-1,Integer::New(4));
    } catch(ArrayIndexOutOfBoundsException e) {
        isException = true;
    }

    if(!isException) {
      TEST_FAIL("[ArrayList<Integer> Test {insert(int index,Integer val)} case2]");
      break;
    }

    Integer ii;
    isException = false;
    try {
        list->insert(-1,ii);
    } catch(ArrayIndexOutOfBoundsException e) {
          isException = true;
    }

    if(!isException) {
      TEST_FAIL("[ArrayList<Integer> Test {insert(int index,Integer val)} case2]");
      break;
    }

    TEST_OK("[ArrayList<Integer> Test {insert(int index,Integer val)}]");
    break;
  }

  //--[_ArrayList<Integer> Test {insert(int index,int val)} Start]
  while(1) {
    ArrayList<Integer>list = ArrayList<Integer>::New();
    list->add(Integer::New(1));
    list->add(Integer::New(2));
    list->add(Integer::New(3));

    list->insert(1,Integer::New(4));
    if(list->get(0)->toValue() != 1
    ||list->get(1)->toValue() != 4
    ||list->get(2)->toValue() != 2
    ||list->get(3)->toValue() != 3) {
      TEST_FAIL("[ArrayList<Integer> Test {insert(int index,int val)} case0]");
      break;
    }

    int size = list->size();
    bool isException = false;
    try {
        int result = list->insert(100,Integer::New(4));
    } catch(ArrayIndexOutOfBoundsException e) {
       isException = true;
    }

    if(!isException) {
      TEST_FAIL("[ArrayList<Integer> Test {insert(int index,int val)} case1]");
      break;
    }

    isException = false;
    try {
        list->insert(-1,Integer::New(4));
    } catch(ArrayIndexOutOfBoundsException e) {
         isException = true;
    }

    if(!isException) {
      TEST_FAIL("[ArrayList<Integer> Test {insert(int index,int val)} case2]");
      break;
    }

    int currentSize = list->size();
    list->insert(0,Integer::New(100));
    if(list->get(0)->toValue() != 100 && (list->size() != (currentSize + 1))) {
      TEST_FAIL("[ArrayList<Integer> Test {insert(int index,int val)} case3]");
      break;
    }

    TEST_OK("[ArrayList<Integer> Test {insert(int index,int val)}]");
    break;
  }

  //int insert(int index,ArrayList<Integer> list);
  while(1) {
    ArrayList<Integer>list = ArrayList<Integer>::New();
    list->add(Integer::New(1));
    list->add(Integer::New(2));
    list->add(Integer::New(3));

    ArrayList<Integer> list2 = ArrayList<Integer>::New();
    list2->add(Integer::New(4));
    list2->add(Integer::New(5));
    list2->add(Integer::New(6));

    list->insert(1,list2);
    if(list->get(0)->toValue() != 1
    ||list->get(1)->toValue() != 4
    ||list->get(2)->toValue() != 5
    ||list->get(3)->toValue() != 6
    ||list->get(4)->toValue() != 2
    ||list->get(5)->toValue() != 3) {
      TEST_FAIL("[ArrayList<Integer> Test {insert(int index,ArrayList<Integer> list)} case0]");
      break;
    }

    int size = list->size();
    bool isException = false;
    try {
        int result = list->insert(100,list2);
    } catch(ArrayIndexOutOfBoundsException e) {
         isException = true;
    }

    if(!isException) {
      TEST_FAIL("[ArrayList<Integer> Test {insert(int index,ArrayList<Integer> list)} case1]");
      break;
    }

    isException = false;
    size = list->size();
    try {
        list->insert(-1,list2);
    } catch(ArrayIndexOutOfBoundsException e) {
        isException = true;
    }

    if(!isException) {
      TEST_FAIL("[ArrayList<Integer> Test {insert(int index,ArrayList<Integer> list)} case2]");
      break;
    }

    ArrayList<Integer>list3 = ArrayList<Integer>::New();
    list3->add(Integer::New(10));
    list3->add(Integer::New(11));
    list3->add(Integer::New(12));

    ArrayList<Integer>list4 = ArrayList<Integer>::New();
    list4->add(Integer::New(13));
    list4->add(Integer::New(14));
    list4->add(Integer::New(15));

    list3->insert(0,list4);
    if(list3->get(0)->toValue() != 13
    ||list3->get(1)->toValue() != 14
    ||list3->get(2)->toValue() != 15
    ||list3->get(3)->toValue() != 10
    ||list3->get(4)->toValue() != 11
    ||list3->get(5)->toValue() != 12) {
      TEST_FAIL("[ArrayList<Integer> Test {insert(int index,ArrayList<Integer> list)} case3]");
      break;
    }

    TEST_OK("[ArrayList<Integer> Test {insert(int index,ArrayList<Integer> list)}]");
    break;
  }

  //int insert(int index,ArrayList<Integer> list,int length);
  while(1) {
    ArrayList<Integer>list = ArrayList<Integer>::New();
    list->add(Integer::New(1));
    list->add(Integer::New(2));
    list->add(Integer::New(3));

    ArrayList<Integer> list2 = ArrayList<Integer>::New();
    list2->add(Integer::New(4));
    list2->add(Integer::New(5));
    list2->add(Integer::New(6));

    list->insert(1,list2,2);
    if(list->get(0)->toValue() != 1
    ||list->get(1)->toValue() != 4
    ||list->get(2)->toValue() != 5
    ||list->get(3)->toValue() != 2
    ||list->get(4)->toValue() != 3) {
      TEST_FAIL("[ArrayList<Integer> Test {insert(int index,ArrayList<Integer> list,int length)} case0]");
      break;
    }

    if(list->size() != 5) {
      TEST_FAIL("[ArrayList<Integer> Test {insert(int index,ArrayList<Integer> list,int length)} case1]");
      break;
    }

    int size = list->size();
    bool isException = false;
    try {
        list->insert(100,list2,5);
    } catch(ArrayIndexOutOfBoundsException e) {
       isException = true;
    }

    if(!isException) {
      TEST_FAIL("[ArrayList<Integer> Test {insert(int index,ArrayList<Integer> list,int length)} case1]");
      break;
    }

    //size != list->size();
    isException = false;
    try {
        list->insert(-1,list2,100);
    } catch(ArrayIndexOutOfBoundsException e) {
       isException = true;
    }

    if(!isException) {
      TEST_FAIL("[ArrayList<Integer> Test {insert(int index,ArrayList<Integer> list,int length)} case2]");
      break;
    }

    ArrayList<Integer>list3 = ArrayList<Integer>::New();
    list3->add(Integer::New(10));
    list3->add(Integer::New(11));
    list3->add(Integer::New(12));

    ArrayList<Integer>list4 = ArrayList<Integer>::New();
    list4->add(Integer::New(13));
    list4->add(Integer::New(14));
    list4->add(Integer::New(15));

    list3->insert(0,list4,2);
    if(list3->get(0)->toValue() != 13
    ||list3->get(1)->toValue() != 14
    ||list3->get(2)->toValue() != 10
    ||list3->get(3)->toValue() != 11
    ||list3->get(4)->toValue() != 12) {
      TEST_FAIL("[ArrayList<Integer> Test {insert(int index,ArrayList<Integer> list,int length)} case3]");
      break;
    }

    if(list3->size() != 5) {
      TEST_FAIL("[ArrayList<Integer> Test {insert(int index,ArrayList<Integer> list,int length)} case4]");
      break;
    }

    ArrayList<Integer>list5 = ArrayList<Integer>::New();
    list5->add(Integer::New(10));
    list5->add(Integer::New(11));
    list5->add(Integer::New(12));

    ArrayList<Integer>list6 = ArrayList<Integer>::New();
    list6->add(Integer::New(13));
    list6->add(Integer::New(14));
    list6->add(Integer::New(15));

    bool isException2 = false;
    try {
      list5->insert(0,list6,100);
    } catch(ArrayIndexOutOfBoundsException e) {
      isException2 = true;
    }

    if(list5->get(0)->toValue() != 10
      ||list5->get(1)->toValue() != 11
      ||list5->get(2)->toValue() != 12) {
      TEST_FAIL("[ArrayList<Integer> Test {insert(int index,ArrayList<Integer> list,int length)} case5]");
      break;
    }

    if(!isException2) {
      TEST_FAIL("[ArrayList<Integer> Test {insert(int index,ArrayList<Integer> list,int length)} case6]");
      break;
    }

    if(list5->size() != 3) {
      TEST_FAIL("[ArrayList<Integer> Test {insert(int index,ArrayList<Integer> list,int length)} case7]");
      break;
    }

    TEST_OK("[ArrayList<Integer> Test {insert(int index,ArrayList<Integer> list,int length)}]");
    break;
  }

  //void insertFirst(Integer val);
  while(1) {
    ArrayList<Integer> list = ArrayList<Integer>::New();
    list->add(Integer::New(1));
    list->add(Integer::New(2));
    list->add(Integer::New(3));

    list->insertFirst(Integer::New(4));
    if(list->get(0)->toValue() != 4
       ||list->get(1)->toValue() != 1
       ||list->get(2)->toValue() != 2
       ||list->get(3)->toValue() != 3) {
         TEST_FAIL("[ArrayList<Integer> Test {insertFirst(Integer val)} case1]");
         break;
    }

    if(list->size() != 4) {
        TEST_FAIL("[ArrayList<Integer> Test {insertFirst(Integer val)} case2]");
        break;
    }

    ArrayList<Integer> list2 = ArrayList<Integer>::New();
    list2->insertFirst(Integer::New(4));
    if(list2->get(0)->toValue() != 4) {
      TEST_FAIL("[ArrayList<Integer> Test {insertFirst(Integer val)} case3]");
      break;
    }

    if(list2->size() != 1) {
      TEST_FAIL("[ArrayList<Integer> Test {insertFirst(Integer val)} case4]");
      break;
    }

    ArrayList<Integer> list3 = ArrayList<Integer>::New();
    Integer nt;
    list3->insertFirst(nt);
    if(list3->size() == 0) {
      TEST_FAIL("[ArrayList<Integer> Test {insertFirst(Integer val)} case5]");
      break;
    }

    TEST_OK("[ArrayList<Integer> Test {insertFirst(Integer val)}]");
    break;
  }

  //void insertFirst(int val);
  while(1) {
    ArrayList<Integer> list = ArrayList<Integer>::New();
    list->add(Integer::New(1));
    list->add(Integer::New(2));
    list->add(Integer::New(3));

    list->insertFirst(Integer::New(4));
    if(list->get(0)->toValue() != 4
       ||list->get(1)->toValue() != 1
       ||list->get(2)->toValue() != 2
       ||list->get(3)->toValue() != 3) {
         TEST_FAIL("[ArrayList<Integer> Test {insertFirst(int val)} case1]");
         break;
    }

    if(list->size() != 4) {
        TEST_FAIL("[ArrayList<Integer> Test {insertFirst(int val)} case2]");
        break;
    }

    ArrayList<Integer> list2 = ArrayList<Integer>::New();
    list2->insertFirst(Integer::New(4));
    if(list2->get(0)->toValue() != 4) {
      TEST_FAIL("[ArrayList<Integer> Test {insertFirst(int val)} case3]");
      break;
    }

    if(list2->size() != 1) {
      TEST_FAIL("[ArrayList<Integer> Test {insertFirst(int val)} case4]");
      break;
    }

    TEST_OK("[ArrayList<Integer> Test {insertFirst(int val)}]");
    break;
  }

  //void insertFirst(ArrayList<Integer> list);
  while(1) {
    ArrayList<Integer> list = ArrayList<Integer>::New();
    list->add(Integer::New(1));
    list->add(Integer::New(2));
    list->add(Integer::New(3));

    ArrayList<Integer> list2 = ArrayList<Integer>::New();
    list2->add(Integer::New(4));
    list2->add(Integer::New(5));
    list2->add(Integer::New(6));
    list->insertFirst(list2);

    if(list->get(0)->toValue() != 4
      ||list->get(1)->toValue() != 5
      ||list->get(2)->toValue() != 6
      ||list->get(3)->toValue() != 1
      ||list->get(4)->toValue() != 2
      ||list->get(5)->toValue() != 3) {
        TEST_FAIL("[ArrayList<Integer> Test {insertFirst(ArrayList<Integer> list)} case1]");
        break;
      }

    ArrayList<Integer> list3 = ArrayList<Integer>::New();
    list3->add(Integer::New(1));
    list3->add(Integer::New(2));

    ArrayList<Integer> list4 = ArrayList<Integer>::New();
    list4->insertFirst(list4);

    if(list3->get(0)->toValue() != 1
      ||list3->get(1)->toValue() != 2){
        TEST_FAIL("[ArrayList<Integer> Test {insertFirst(ArrayList<Integer> list)} case2]");
        break;
      }

    if(list3->size() != 2) {
      TEST_FAIL("[ArrayList<Integer> Test {insertFirst(ArrayList<Integer> list)} case3]");
      break;
    }

/*
    ArrayList<Integer> list5;
    list3->insertFirst(list5);
    if(list3->size() != 2) {
      TEST_FAIL("[ArrayList<Integer> Test {insertFirst(ArrayList<Integer> list)} case4]");
      break;
    }
*/
    TEST_OK("[ArrayList<Integer> Test {insertFirst(ArrayList<Integer> list)}]");
    break;
  }

  //void insertLast(Integer v);
  while(1) {
    ArrayList<Integer> list = ArrayList<Integer>::New();
    list->add(Integer::New(1));
    list->add(Integer::New(2));
    list->add(Integer::New(3));

    list->insertLast(Integer::New(4));
    if(list->get(0)->toValue() != 1
      ||list->get(1)->toValue() != 2
      ||list->get(2)->toValue() != 3
      ||list->get(3)->toValue() != 4) {
        TEST_FAIL("[ArrayList<Integer> Test {insertLast(Integer v)} case1]");
        break;
    }

    if(list->size() != 4) {
      TEST_FAIL("[ArrayList<Integer> Test {insertLast(Integer v)} case2]");
      break;
    }

    ArrayList<Integer> list2 = ArrayList<Integer>::New();
    list2->add(Integer::New(1));
    list2->add(Integer::New(2));
    list2->add(Integer::New(3));
    Integer t2;
    list2->insertLast(t2);

    if(list2->get(0)->toValue() != 1
      ||list2->get(1)->toValue() != 2
      ||list2->get(2)->toValue() != 3) {
        TEST_FAIL("[ArrayList<Integer> Test {insertLast(Integer v)} case3]");
        break;
    }

    if(list2->size() != 4) {
      TEST_FAIL("[ArrayList<Integer> Test {insertLast(Integer v)} case4]");
      break;
    }

    TEST_OK("[ArrayList<Integer> Test {insertLast(Integer v)} case5]");
    break;
  }

  //void insertLast(int v);
  while(1) {
    ArrayList<Integer> list = ArrayList<Integer>::New();
    list->add(Integer::New(1));
    list->add(Integer::New(2));
    list->add(Integer::New(3));

    list->insertLast(Integer::New(4));
    if(list->get(0)->toValue() != 1
      ||list->get(1)->toValue() != 2
      ||list->get(2)->toValue() != 3
      ||list->get(3)->toValue() != 4) {
        TEST_FAIL("[ArrayList<Integer> Test {insertLast(int v)} case1]");
        break;
    }

    if(list->size() != 4) {
      TEST_FAIL("[ArrayList<Integer> Test {insertLast(int v)} case2]");
      break;
    }

    ArrayList<Integer> list2 = ArrayList<Integer>::New();
    list2->insertLast(Integer::New(1));

    if(list2->size() != 1) {
      TEST_FAIL("[ArrayList<Integer> Test {insertLast(int v)} case3]");
      break;
    }

    if(list2->get(0)->toValue() != 1) {
      TEST_FAIL("[ArrayList<Integer> Test {insertLast(int v)} case4]");
      break;
    }

    TEST_OK("[ArrayList<Integer> Test {insertLast(int v)} case5]");
    break;
  }

  //insertLast(ArrayList<Integer> list);
  while(1) {
    ArrayList<Integer> list = ArrayList<Integer>::New();
    list->add(Integer::New(1));
    list->add(Integer::New(2));
    list->add(Integer::New(3));

    ArrayList<Integer> list2 = ArrayList<Integer>::New();
    list2->add(Integer::New(4));
    list2->add(Integer::New(5));
    list2->add(Integer::New(6));

    list->insertLast(list2);
    if(list->get(0)->toValue() != 1
      ||list->get(1)->toValue() != 2
      ||list->get(2)->toValue() != 3
      ||list->get(3)->toValue() != 4
      ||list->get(4)->toValue() != 5
      ||list->get(5)->toValue() != 6) {
        TEST_FAIL("[ArrayList<Integer> Test {insertLast(ArrayList<Integer> v)} case1]");
        break;
    }

    if(list->size() != 6) {
        TEST_FAIL("[ArrayList<Integer> Test {insertLast(ArrayList<Integer> v)} case2]");
        break;
    }

    ArrayList<Integer> list3 = ArrayList<Integer>::New();
    list3->add(Integer::New(1));
    list3->add(Integer::New(2));
    list3->add(Integer::New(3));
/*
    ArrayList<Integer> list4;
    list3->insertLast(list4);
*/
    if(list3->get(0)->toValue() != 1
      ||list3->get(1)->toValue() != 2
      ||list3->get(2)->toValue() != 3) {
        TEST_FAIL("[ArrayList<Integer> Test {insertLast(ArrayList<Integer> v)} case3]");
        break;
    }

    if(list3->size() != 3) {
        TEST_FAIL("[ArrayList<Integer> Test {insertLast(ArrayList<Integer> v)} case4]");
        break;
    }

    TEST_OK("[ArrayList<Integer> Test {insertLast(ArrayList<Integer> v)} case5]");
    break;
  }

  //int size();
  while(1) {
    ArrayList<Integer> list = ArrayList<Integer>::New();
    list->add(Integer::New(1));
    list->add(Integer::New(2));
    list->add(Integer::New(3));
    if(list->size() != 3) {
      TEST_FAIL("[ArrayList<Integer> Test {size()} case1]");
      break;
    }

    ArrayList<Integer> list2 = ArrayList<Integer>::New();
    if(list2->size() != 0) {
      TEST_FAIL("[ArrayList<Integer> Test {size()} case2]");
      break;
    }

    TEST_OK("[ArrayList<Integer> Test {size()} case3]");
    break;
  }

  //ListIterator<Integer> getValue;
  while(1) {
    ArrayList<Integer> list = ArrayList<Integer>::New();
    list->add(Integer::New(1));
    list->add(Integer::New(2));
    list->add(Integer::New(3));
    list->add(Integer::New(4));
    list->add(Integer::New(5));

    auto iterator = list->getIterator();
    int index = 1;
    while(iterator->hasValue() && index != list->size()) {
      Integer v = iterator->getValue();
      if(v->toValue() != index) {
        TEST_FAIL("[ListIterator<Integer> Test {getValue()} case1]");
        break;
      }

      iterator->next();
      index++;
    }

    ArrayList<Integer> list1 = ArrayList<Integer>::New();
    auto iterator1 = list1->getIterator();
    bool isException = false;
    try {
        Integer v = iterator1->getValue();
    } catch(ArrayIndexOutOfBoundsException e) {
       isException = true;
    }

    if(!isException) {
      TEST_FAIL("[ListIterator<Integer> Test {getValue()} case2]");
      break;
    }

    TEST_OK("[ListIterator<Integer> Test {getValue()} case3]");
    break;
  }

  //ListIterator<Integer> hasValue();
  while(1) {
    ArrayList<Integer> list = ArrayList<Integer>::New();
    list->add(Integer::New(1));
    list->add(Integer::New(2));
    list->add(Integer::New(3));
    auto iterator = list->getIterator();
    if(!iterator->hasValue()) {
      TEST_FAIL("[ListIterator<Integer> Test {hasValue()} case1]");
      break;
    }

    iterator->next();
    iterator->next();
    iterator->next();

    if(iterator->hasValue()) {
      TEST_FAIL("[ListIterator<Integer> Test {hasValue()} case2]");
      break;
    }

    ArrayList<Integer> list2 = ArrayList<Integer>::New();
    auto iterator2 = list2->getIterator();
    if(iterator2->hasValue()) {
      TEST_FAIL("[ListIterator<Integer> Test {hasValue()} case3]");
      break;
    }

    TEST_OK("[ListIterator<Integer> Test {hasValue()} case4]");
    break;
  }

  // ListIterator<Integer> next();
  while(1) {
    ArrayList<Integer> list = ArrayList<Integer>::New();
    list->add(Integer::New(1));
    list->add(Integer::New(2));
    list->add(Integer::New(3));
    auto iterator = list->getIterator();

    iterator->next();
    Integer v1 = iterator->getValue();

    iterator->next();
    Integer v2 = iterator->getValue();

    if(iterator->next()) {
      TEST_FAIL("[ListIterator<Integer> Test {next()} case1]");
      break;
    }

    ArrayList<Integer> list2 = ArrayList<Integer>::New();
    auto iterator2 = list2->getIterator();
    if(iterator2->next()) {
      TEST_FAIL("[ListIterator<Integer> Test {next()} case2]");
    }

    TEST_OK("[ListIterator<Integer> Test {next()} case3]");
    break;
  }

  //--[_ListIterator<Integer> Test {remove()} Start]
  while(1) {
    ArrayList<Integer> list = ArrayList<Integer>::New();
    list->add(Integer::New(1));
    list->add(Integer::New(2));
    list->add(Integer::New(3));
    list->add(Integer::New(4));
    list->add(Integer::New(5));
    auto iterator = list->getIterator();
    while(iterator->hasValue()) {
      if(iterator->getValue()->toValue() == 3) {
        iterator->remove();
      }else {
        iterator->next();
      }
    }

    if(list->size() != 4) {
        TEST_FAIL("[ListIterator<Integer> Test {remove()} case0]");
        break;
    }

    if(list->get(0)->toValue() != 1 ||list->get(1)->toValue() != 2
      ||list->get(2)->toValue() != 4||list->get(3)->toValue() != 5) {
        TEST_FAIL("[ListIterator<Integer> Test {remove()} case2]");
        break;
    }

    TEST_OK("[_ListIterator<Integer> Test {remove()} case3]");
    break;
  }
}
