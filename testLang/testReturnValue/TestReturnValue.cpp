#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Boolean.hpp"
#include "StrongPointer.hpp"
#include "IllegalArgumentException.hpp"
#include "NullPointerException.hpp"
#include "InitializeException.hpp"
#include "TestLog.hpp"
#include "Error.hpp"
#include "OStdReturnValue.hpp"
#include "String.hpp"

using namespace obotcha;

DefRet(String,Integer) getValue() {
  return MakeRet(createString("hello1"),createInteger(100));
}

void testReturnValue() {
  String v1;
  Integer v2;
  FetchRet(v1,v2) = getValue();
  if(v1 == nullptr || !v1->equals("hello1")) {
    TEST_FAIL("testReturnValue case1");
  }

  if(v2 == nullptr || v2->toValue() != 100) {
    TEST_FAIL("testReturnValue case2");
  }

  TEST_OK("testReturnValue case100");
}
