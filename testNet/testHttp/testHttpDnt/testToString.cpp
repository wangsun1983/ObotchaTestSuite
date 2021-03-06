#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "HttpMime.hpp"
#include "HttpHeaderDnt.hpp"
#include "TestLog.hpp"

using namespace obotcha;

void testToString() {
  while(1) {
    HttpHeaderDnt dnt = createHttpHeaderDnt();
    dnt->import("1");
    if(!dnt->toString()->equals("1")) {
      TEST_FAIL("[HttpHeaderDnt test toString case1]");
      break;
    }
    break;
  }

  while(1) {
    HttpHeaderDnt dnt = createHttpHeaderDnt();
    dnt->import("0");
    if(!dnt->toString()->equals("0")) {
      TEST_FAIL("[HttpHeaderDnt test toString case2]");
      break;
    }
    break;
  }

  TEST_OK("[HttpHeaderDnt test toString case100]");

}
