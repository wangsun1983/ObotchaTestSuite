#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "HttpMime.hpp"
#include "HttpHeaderRetryAfter.hpp"
#include "Calendar.hpp"
#include "TestLog.hpp"
#include "HttpHeader.hpp"

using namespace obotcha;

void testSet() {
  while(1) {
    HttpHeaderRetryAfter retryAfter = HttpHeaderRetryAfter::New();
    HttpDate date = HttpDate::New(String::New(" Wed, 21 Oct 2015 07:28:00 GMT "));
    retryAfter->setDate(date);
    if(!retryAfter->toString()->sameAs("Wed, 21 Oct 2015 07:28:00 GMT")) {
      TEST_FAIL("[HttpHeaderRetryAfter test set case1]");
    }
    break;
  }

  while(1) {
    HttpHeaderRetryAfter retryAfter = HttpHeaderRetryAfter::New();
    //retryAfter->load(" 120 ");
    retryAfter->setDelayInterval(120);
    if(!retryAfter->toString()->sameAs("120")) {
      TEST_FAIL("[HttpHeaderRetryAfter test set case2]");
    }
    break;
  }
  
  TEST_OK("[HttpHeaderRetryAfter test set case100]");
}
