#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "HttpMime.hpp"
#include "HttpHeaderAcceptPatch.hpp"
#include "TestLog.hpp"

using namespace obotcha;

void testPatchToString() {
  while(1) {
    HttpHeaderAcceptPatch encoding1 = createHttpHeaderAcceptPatch();
    encoding1->import("application/example,text/example");
    if(!encoding1->toString()->equals("application/example,text/example")) {
      TEST_FAIL("[HttpHeaderAcceptPatch test Parse case1]");
    }
    break;
  }

  while(1) {
    HttpHeaderAcceptPatch encoding1 = createHttpHeaderAcceptPatch();
    encoding1->import("text/example;charset=utf-8");
    if(!encoding1->toString()->equals("text/example;charset=utf-8")) {
      TEST_FAIL("[HttpHeaderAcceptPatch test Parse case2]");
    }

    break;
  }

  while(1) {
    HttpHeaderAcceptPatch encoding1 = createHttpHeaderAcceptPatch();
    encoding1->import("application/merge-patch+json");
    if(!encoding1->toString()->equals("application/merge-patch+json")) {
      TEST_FAIL("[HttpHeaderAcceptPatch test Parse case3]");
    }
    break;
  }

  TEST_OK("[HttpHeaderAcceptPatch test toString case100]");

}
