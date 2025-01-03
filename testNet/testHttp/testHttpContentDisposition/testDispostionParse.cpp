#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "HttpMime.hpp"
#include "HttpHeaderContentDisposition.hpp"
#include "Math.hpp"
#include "TestLog.hpp"

using namespace obotcha;

void testDispositionParse() {
  while(1) {
    HttpHeaderContentDisposition disposition = HttpHeaderContentDisposition::New();
    disposition->load("attachment");
    if(disposition->getType() != st(HttpHeaderContentDisposition)::Attachment) {
        TEST_FAIL("[HttpHeaderContentDisposition test Parse case1],type is %d",disposition->getType());
        break;
    }
    break;
  }

  while(1) {
    HttpHeaderContentDisposition disposition = HttpHeaderContentDisposition::New();
    disposition->load("attachment; filename=\"filename.jpg\"");
    if(disposition->getType() != st(HttpHeaderContentDisposition)::Attachment) {
        TEST_FAIL("[HttpHeaderContentDisposition test Parse case2]");
        break;
    }

    if(!disposition->getFileName()->sameAs("filename.jpg")) {
        TEST_FAIL("[HttpHeaderContentDisposition test Parse case3]");
        break;
    }
    break;
  }

  while(1) {
    HttpHeaderContentDisposition disposition = HttpHeaderContentDisposition::New();
    disposition->load("form-data; name=\"fieldName\"; filename=\"filename.jpg\"");
    if(disposition->getType() != st(HttpHeaderContentDisposition)::FormData) {
        TEST_FAIL("[HttpHeaderContentDisposition test Parse case4]");
        break;
    }

    if(!disposition->getFileName()->sameAs("filename.jpg")) {
        TEST_FAIL("[HttpHeaderContentDisposition test Parse case5]");
        break;
    }

    if(!disposition->getName()->sameAs("fieldName")) {
        TEST_FAIL("[HttpHeaderContentDisposition test Parse case6]");
        break;
    }
    break;
  }

  TEST_OK("[HttpHeaderContentDisposition test Parse case100]");

}
