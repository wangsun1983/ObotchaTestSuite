#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "HttpMime.hpp"
#include "HttpHeaderProxyAuthorization.hpp"
#include "Math.hpp"
#include "TestLog.hpp"

using namespace obotcha;

void testProxyAUthorizationParse() {
  while(1) {
    HttpHeaderProxyAuthorization proxy = HttpHeaderProxyAuthorization::New();
    proxy->load("Basic YWxhZGRpbjpvcGVuc2VzYW1l");
    if(!proxy->type->sameAs("Basic")) {
      TEST_FAIL("[HttpHeaderProxyAuthorization test Parse case10]");
    }

    if(!proxy->credentials->sameAs("YWxhZGRpbjpvcGVuc2VzYW1l")) {
      TEST_FAIL("[HttpHeaderProxyAuthorization test Parse case10]");
    }

    break;
  }

  TEST_OK("[HttpHeaderProxyAuthorization test Parse case100]");
}
