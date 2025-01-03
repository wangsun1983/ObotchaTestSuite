#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "HttpMime.hpp"
#include "HttpHeaderAccept.hpp"
#include "HttpHeaderLastModified.hpp"
#include "TestLog.hpp"

using namespace obotcha;

void testToString() {
  while(1) {
    HttpHeaderLastModified headerDate = HttpHeaderLastModified::New();
    headerDate->load(" Wed, 21 Oct 2015 07:28:00 GMT");
    if(!headerDate->toString()->sameAs("Wed, 21 Oct 2015 07:28:00 GMT")) {
      TEST_FAIL("[HttpHeaderLastModified test toString case1]");
    }
    break;
  }

  TEST_OK("[HttpHeaderLastModified test toString case100]");

}
