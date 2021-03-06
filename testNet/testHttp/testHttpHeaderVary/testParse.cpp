#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "HttpMime.hpp"
#include "HttpHeaderVary.hpp"
#include "Math.hpp"
#include "TestLog.hpp"

using namespace obotcha;

void testParse() {
  while(1) {
    HttpHeaderVary match = createHttpHeaderVary();
    match->import("no-referrer, User-Agent");

    ArrayList<String> list = match->get();
    if(list->size() != 2) {
      TEST_FAIL("[HttpHeaderVary test Parse case1]");
      break;
    }

    if(!list->get(0)->equals("no-referrer") || !list->get(1)->equals("User-Agent")) {
      TEST_FAIL("[HttpHeaderVary test Parse case2]");
      break;
    }
    break;
  }

  TEST_OK("[HttpHeaderVary test Parse case100]");
}
