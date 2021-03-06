#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "HttpMime.hpp"
#include "HttpHeaderSourceMap.hpp"
#include "TestLog.hpp"

using namespace obotcha;

void testToString() {
  while(1) {
    HttpHeaderSourceMap timing = createHttpHeaderSourceMap();
    timing->import("/path/to/file.js.map");
    if(!timing->toString()->equals("/path/to/file.js.map")) {
      TEST_FAIL("[HttpHeaderSourceMap test toString case1]");
      break;
    }
    break;
  }

  TEST_OK("[HttpHeaderServerTiming test toString case100]");

}
