#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "HttpMime.hpp"
#include "HttpHeaderAccept.hpp"
#include "Math.hpp"
#include "HttpHeaderAccessControlExposeHeaders.hpp"
#include "HttpMethod.hpp"
#include "TestLog.hpp"

using namespace obotcha;

void testParse() {
  while(1) {
    HttpHeaderAccessControlExposeHeaders c = HttpHeaderAccessControlExposeHeaders::New();
    c->load("Content-Length, X-Kuma-Revision");
    auto list = c->get();
    String v0 = list->get(0);
    if(!v0->sameAs("Content-Length")) {
      TEST_FAIL("[HttpHeaderAccessControlExposeHeaders test Parse case1]");
      break;
    }

    String v1 = list->get(1);
    if(!v1->sameAs("X-Kuma-Revision")) {
      TEST_FAIL("[HttpHeaderAccessControlExposeHeaders test Parse case2]");
      break;
    }
    break;
  }
  
  while(1) {
    HttpHeaderAccessControlExposeHeaders c = HttpHeaderAccessControlExposeHeaders::New("Content-Length, X-Kuma-Revision");
    auto list = c->get();
    String v0 = list->get(0);
    if(!v0->sameAs("Content-Length")) {
      TEST_FAIL("[HttpHeaderAccessControlExposeHeaders test Parse case3]");
      break;
    }

    String v1 = list->get(1);
    if(!v1->sameAs("X-Kuma-Revision")) {
      TEST_FAIL("[HttpHeaderAccessControlExposeHeaders test Parse case4]");
      break;
    }
    break;
  }

  TEST_OK("[HttpHeaderAccessControlExposeHeaders test Parse case100]");

}
