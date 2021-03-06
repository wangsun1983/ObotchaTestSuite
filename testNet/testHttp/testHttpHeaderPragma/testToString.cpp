#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "HttpMime.hpp"
#include "HttpHeaderPragma.hpp"
#include "TestLog.hpp"

using namespace obotcha;

void testToString() {
  while(1) {
    HttpHeaderPragma pragma = createHttpHeaderPragma();
    pragma->import(" no-cache ");
    if(!pragma->toString()->equals("no-cache")){
      TEST_FAIL("[HttpHeaderPragma test toString case1]");
      break;
    }
    break;
  }

  TEST_OK("[HttpHeaderPragma test toString case100]");
}
