#include <stdio.h>
#include <unistd.h>

#include "Stack.hpp"
#include "TestLog.hpp"
#include "String.hpp"
using namespace obotcha;

void testStackPop() {
  while(1) {
    Stack<String> ss = Stack<String>::New();
    ss->push(String::New("a"));
    ss->push(String::New("b"));
    ss->push(String::New("c"));
    
    auto v_c = ss->pop();
    auto v_b = ss->pop();
    auto v_a = ss->pop();
    
    if(ss->size() != 0) {
        TEST_FAIL("testStack pop case1");
    }
    
    if(!v_a->sameAs("a") || !v_b->sameAs("b") || !v_c->sameAs("c")) {
        TEST_FAIL("testStack pop case2");
    }
    break;
  }
  
  while(1) {
    Stack<String> ss = Stack<String>::New();
    for(int i = 0;i < 32*1024;i++) {
        ss->push(String::New(i));
    }
    
    for(int j = 32*1024-1;j >= 0;j--) {
        auto v = ss->pop();
        if(!v->equals(String::New(j))) {
            TEST_FAIL("testStack pop case3,v is %s,j is %d",v->toChars(),j);
            break;
        }
    }
    break;
  }
  TEST_OK("testStack pop test100");
}
