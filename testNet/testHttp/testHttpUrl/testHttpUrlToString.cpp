#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "HttpMime.hpp"
#include "HttpHeaderParser.hpp"
#include "ByteRingArrayReader.hpp"
#include "HttpMethod.hpp"
#include "TestLog.hpp"

using namespace obotcha;

void testHttpUrlToString() {
  while(1) {
    const char *raw= "/demo";
    HttpUrl url = createHttpUrl(raw);
    if(!url->toString()->equals("/demo")) {
        TEST_FAIL("HttpUrl toString case1,url is %s",url->toString()->toChars());
    }
    break;
  }

  while(1) {
    String request =  "http://su:abc@localhost:1234/test.cgi?a=b&c=d#fffsss";
    HttpUrl url = createHttpUrl(request);
    if(!url->toString()->equals("http://su:abc@localhost:1234/test.cgi?a=b&c=d#fffsss")
        &&!url->toString()->equals("http://su:abc@localhost:1234/test.cgi?c=d&a=b#fffsss")) {
        TEST_FAIL("HttpUrl toString case3,url is %s",url->toString()->toChars());
    }
    break;
  }

  while(1) {
    String request =  "http://abdd@localhost/test.cgi?a=b&c=d";
    HttpUrl url = createHttpUrl(request);
    if(!url->toString()->equals("http://abdd@localhost/test.cgi?a=b&c=d")
        &&!url->toString()->equals("http://abdd@localhost/test.cgi?c=d&a=b")) {
        TEST_FAIL("HttpUrl toString case4,url is %s",url->toString()->toChars());
    }
    break;
  }

  while(1) {
    HttpUrl url =  createHttpUrl("https://su:abc@localhost/test/wangsl/01234");
    if(!url->toString()->equals("https://su:abc@localhost/test/wangsl/01234")) {
        TEST_FAIL("HttpUrl toString case5,url is %s",url->toString()->toChars());
    }
    break;
  }

  while(1) {
    HttpUrl url =  createHttpUrl("https://ssaabb/test/wangsl/01234");
    if(!url->toString()->equals("https://ssaabb/test/wangsl/01234")) {
        TEST_FAIL("HttpUrl toString case6,url is %s",url->toString()->toChars());
    }
    break;
  }

  while(1) {
    HttpUrl url =  createHttpUrl("https://ssaabb:123");
    if(!url->toString()->equals("https://ssaabb:123")) {
        TEST_FAIL("HttpUrl toString case7,url is %s",url->toString()->toChars());
    }
    break;
  }

  while(1) {
    String request =  "su:abc@localhost:1234/test.cgi?a=b&c=d#fffsss";
    HttpUrl url = createHttpUrl(request);
    if(!url->toString()->equals("su:abc@localhost:1234/test.cgi?a=b&c=d#fffsss")
        &&!url->toString()->equals("su:abc@localhost:1234/test.cgi?c=d&a=b#fffsss")) {
        TEST_FAIL("HttpUrl toString case8,url is %s",url->toString()->toChars());
    }
    break;
  }

  while(1) {
    HttpUrl url =  createHttpUrl("https://ssaabb:123#frag");
    if(!url->toString()->equals("https://ssaabb:123#frag")) {
        TEST_FAIL("HttpUrl toString case9,url is %s",url->toString()->toChars());
    }
    break;
  }
  
  while(1) {
    HttpUrl url =  createHttpUrl("https://ssaabb:123#frag");
    url->setFragment("aaaac");
    if(!url->toString()->equals("https://ssaabb:123#aaaac")) {
        TEST_FAIL("HttpUrl toString case10,url is %s",url->toString()->toChars());
    }
    break;
  }

  TEST_OK("[HttpUrlParse test toString case100]");

}