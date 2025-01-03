#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "HttpMime.hpp"
#include "HttpHeaderAcceptCh.hpp"
#include "TestLog.hpp"
#include "HttpHeader.hpp"

using namespace obotcha;

void testSetToHeader() {
  while(1) {
    HttpHeader header = HttpHeader::New();
    header->set(String::New("Accept-CH"),String::New("DPR, Viewport-Width, Width"));
    auto acceptCh = header->getAcceptCh();
    if(!acceptCh->toString()->sameAs("DPR, Viewport-Width, Width")) {
      TEST_FAIL("[HttpHeaderAcceptCh test toString case1]");
      break;
    }
    break;
  }
  
  while(1) {
    HttpHeader header = HttpHeader::New();
    auto acceptCh = HttpHeaderAcceptCh::New();
    acceptCh->load("DPR, Viewport-Width, Width");
    header->setAcceptCh(acceptCh);
    
    auto acceptCh2 = header->getAcceptCh();
    if(!acceptCh2->toString()->sameAs("DPR, Viewport-Width, Width")) {
      TEST_FAIL("[HttpHeaderAcceptCh test toString case2]");
      break;
    }
    break;
  }

  TEST_OK("[HttpHeaderAcceptCh test toString case100]");

}
