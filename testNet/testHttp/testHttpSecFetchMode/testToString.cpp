#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "HttpMime.hpp"
#include "HttpHeaderSecFetchMode.hpp"
#include "TestLog.hpp"

using namespace obotcha;

void testToString() {
  while(1) {
    HttpHeaderSecFetchMode save = createHttpHeaderSecFetchMode();
    save->import("navigate");
    if(!save->toString()->equals("navigate")) {
      TEST_FAIL("[HttpHeaderSecFetchMode test toString case1]");
      break;
    }
    break;
  }

  while(1) {
    HttpHeaderSecFetchMode save = createHttpHeaderSecFetchMode();
    save->import("nested-navigate");
    if(!save->toString()->equals("nested-navigate")) {
      TEST_FAIL("[HttpHeaderSecFetchMode test toString case2]");
      break;
    }
    break;
  }

  TEST_OK("[HttpHeaderSecFetchMode test toString case100]");

}
