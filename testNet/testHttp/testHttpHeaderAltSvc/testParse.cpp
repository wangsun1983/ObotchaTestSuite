#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "HttpMime.hpp"
#include "HttpHeaderAltSvc.hpp"
#include "Math.hpp"
#include "TestLog.hpp"

using namespace obotcha;

void testParse() {
  while(1) {
    HttpHeaderAltSvc svc = createHttpHeaderAltSvc();
    svc->import(" h2=\"alt.example.com:8000\", h2=\":443\"; ma=2592000; persist=1");
    auto svcList = svc->getServices();
    if(svcList->size() != 2) {
      TEST_FAIL("[HttpHeaderAltSvc test Parse case1]");
      break;
    }

    auto item1 = svcList->get(0);
    if(!item1->serviceName->equals("h2")) {
      TEST_FAIL("[HttpHeaderAltSvc test Parse case2]");
      break;
    }

    if(!item1->url->getHost()->equals("alt.example.com")) {
      TEST_FAIL("[HttpHeaderAltSvc test Parse case3]");
      break;
    }

    if(item1->url->getPort() != 8000) {
      TEST_FAIL("[HttpHeaderAltSvc test Parse case4] port is %d",item1->url->getPort());
      break;
    }

    auto item2 = svcList->get(1);
    if(!item2->serviceName->equals("h2")) {
      TEST_FAIL("[HttpHeaderAltSvc test Parse case5]");
      break;
    }

    if(item2->url->getHost() != nullptr) {
      TEST_FAIL("[HttpHeaderAltSvc test Parse case6]");
      break;
    }

    if(item2->url->getPort() != 443) {
      TEST_FAIL("[HttpHeaderAltSvc test Parse case7]");
      break;
    }

    if(svc->getMaxAge() != 2592000) {
      TEST_FAIL("[HttpHeaderAltSvc test Parse case8]");
      break;
    }

    if(svc->getPersist() != 1) {
      TEST_FAIL("[HttpHeaderAltSvc test Parse case9]");
      break;
    }

    break;
  }

  TEST_OK("[HttpHeaderAltSvc test Parse case100]");

}
