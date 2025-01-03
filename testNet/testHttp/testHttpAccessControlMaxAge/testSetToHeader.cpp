#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "HttpMime.hpp"
#include "HttpHeaderAccept.hpp"
#include "Math.hpp"
#include "HttpHeaderAccessControlMaxAge.hpp"
#include "HttpMethod.hpp"
#include "TestLog.hpp"
#include "HttpHeader.hpp"

using namespace obotcha;

void testSetToHeader() {
  while(1) {
    HttpHeader header = HttpHeader::New();
    header->set(String::New("Access-Control-Max-Age"),
                String::New("600"));
    auto c = header->getMaxAge();
    c->load("600");
    if(c->get() != 600) {
      TEST_FAIL("[HttpHeaderAccessControlMaxAge test SetToHeader case1]");
      break;
    }
    break;
  }

  TEST_OK("[HttpHeaderAccessControlMaxAge test SetToHeader case100]");
}
