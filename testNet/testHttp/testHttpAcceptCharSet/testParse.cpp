#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "HttpMime.hpp"
#include "HttpHeaderAcceptCharSet.hpp"
#include "Math.hpp"
#include "TestLog.hpp"

using namespace obotcha;

void testCharSetParse() {
  while(1) {
    HttpHeaderAcceptCharSet charset = createHttpHeaderAcceptCharSet();
    charset->import("iso-8859-1");
    ArrayList<HttpHeaderAcceptCharSetItem> charsets = charset->get();
    if(charsets->size() != 1) {
      TEST_FAIL("[HttpHeaderAcceptCharSet test Parse case1]");
      break;
    }

    if(!charsets->get(0)->type->equals("iso-8859-1")) {
        TEST_FAIL("[HttpHeaderAcceptCharSet test Parse case2]");
        break;
    }
    break;
  }

  while(1) {
    HttpHeaderAcceptCharSet charset = createHttpHeaderAcceptCharSet();
    charset->import("utf-8, iso-8859-1;q=0.5");
    ArrayList<HttpHeaderAcceptCharSetItem> charsets = charset->get();
    if(charsets->size() != 2) {
      TEST_FAIL("[HttpHeaderAcceptCharSet test Parse case3]");
      break;
    }

    if(!charsets->get(0)->type->equals("utf-8")) {
        TEST_FAIL("[HttpHeaderAcceptCharSet test Parse case4]");
        break;
    }

    if(!charsets->get(1)->type->equals("iso-8859-1")) {
        TEST_FAIL("[HttpHeaderAcceptCharSet test Parse case5]");
        break;
    }

    if(charsets->get(1)->weight != 0.5) {
        TEST_FAIL("[HttpHeaderAcceptCharSet test Parse case6]");
        break;
    }
    break;
  }

  while(1) {
    HttpHeaderAcceptCharSet charset = createHttpHeaderAcceptCharSet();
    charset->import("utf-8, iso-8859-1;q=0.5, *;q=0.1");
    ArrayList<HttpHeaderAcceptCharSetItem> charsets = charset->get();
    if(charsets->size() != 3) {
      TEST_FAIL("[HttpHeaderAcceptCharSet test Parse case7]");
      break;
    }

    if(!charsets->get(0)->type->equals("utf-8")) {
        TEST_FAIL("[HttpHeaderAcceptCharSet test Parse case8]");
        break;
    }

    if(!charsets->get(1)->type->equals("iso-8859-1")) {
        TEST_FAIL("[HttpHeaderAcceptCharSet test Parse case9]");
        break;
    }

    if(charsets->get(1)->weight != 0.5) {
        TEST_FAIL("[HttpHeaderAcceptCharSet test Parse case10]");
        break;
    }

    if(!charsets->get(2)->type->equals("*")) {
        TEST_FAIL("[HttpHeaderAcceptCharSet test Parse case11]");
        break;
    }

    if(st(Math)::compareFloat(charsets->get(2)->weight,0.1) != st(Math)::AlmostEqual) {
        TEST_FAIL("[HttpHeaderAcceptCharSet test Parse case12],weight is %f",charsets->get(2)->weight);
        break;
    }
    break;
  }

  TEST_OK("[HttpHeaderAcceptCharSet test Parse case100]");

}
