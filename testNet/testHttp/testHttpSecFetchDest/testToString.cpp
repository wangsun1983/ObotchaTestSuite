#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "HttpMime.hpp"
#include "HttpHeaderSecFetchDest.hpp"
#include "TestLog.hpp"

using namespace obotcha;

void testToString() {
  while(1) {
    HttpHeaderSecFetchDest save = HttpHeaderSecFetchDest::New();
    save->load("track");
    if(!save->toString()->sameAs("track")) {
      TEST_FAIL("[HttpHeaderSecFetchDest test toString case1]");
      break;
    }
    break;
  }

  while(1) {
    HttpHeaderSecFetchDest save = HttpHeaderSecFetchDest::New();
    save->load("audio");
    if(!save->toString()->sameAs("audio")) {
      TEST_FAIL("[HttpHeaderSecFetchDest test toString case2]");
      break;
    }
    break;
  }

  TEST_OK("[HttpHeaderSecFetchDest test toString case100]");

}
