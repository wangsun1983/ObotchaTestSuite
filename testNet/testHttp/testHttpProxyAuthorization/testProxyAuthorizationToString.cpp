#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "HttpMime.hpp"
#include "HttpHeaderProxyAuthorization.hpp"
#include "TestLog.hpp"

using namespace obotcha;

void testProxyAUthorizationToString() {
  while(1) {
    HttpHeaderProxyAuthorization proxy = createHttpHeaderProxyAuthorization();
    proxy->import("Basic YWxhZGRpbjpvcGVuc2VzYW1l");
    if(!proxy->toString()->equals("Basic YWxhZGRpbjpvcGVuc2VzYW1l")) {
      TEST_FAIL("[HttpHeaderProxyAuthorization test toString case1]");
    }
    break;
  }

  TEST_OK("[HttpHeaderProxyAuthorization test toString case100]");
}
