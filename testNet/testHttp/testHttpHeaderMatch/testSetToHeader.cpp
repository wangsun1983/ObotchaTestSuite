#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "HttpMime.hpp"
#include "HttpHeaderMatch.hpp"
#include "Math.hpp"
#include "TestLog.hpp"
#include "HttpHeader.hpp"

using namespace obotcha;

void testSetToHeader() {
  while(1) {
    HttpHeader header = createHttpHeader();
    header->set(createString("If-Match"),
                createString("\"bfc13a64729c4290ef5b2c2730249c88ca92d82d\""));
    auto match = header->getIfMatch();
    ArrayList<HttpHeaderMatchItem> list = match->get();
    if(list->size() != 1){
      TEST_FAIL("[HttpHeaderMatch test setToHeader case1] ");
      break;
    }

    auto item = list->get(0);
    if(item == nullptr || !item->tag->equals("bfc13a64729c4290ef5b2c2730249c88ca92d82d")) {
      TEST_FAIL("[HttpHeaderMatch test setToHeader case2] ");
    }
    break;
  }

  while(1) {
    HttpHeader header = createHttpHeader();
    header->set(createString("If-Match"),
                createString("W/\"67ab43\", \"54ed21\", \"7892dd\""));
    auto match = header->getIfMatch();
    ArrayList<HttpHeaderMatchItem> list = match->get();
    if(list->size() != 3){
      TEST_FAIL("[HttpHeaderMatch test setToHeader case3] ");
      break;
    }

    auto item = list->get(0);
    if(item == nullptr || !item->tag->equals("67ab43") || !item->isWeakAlg) {
      TEST_FAIL("[HttpHeaderMatch test setToHeader case4] ");
    }

    item = list->get(1);
    if(item == nullptr || !item->tag->equals("54ed21") || item->isWeakAlg) {
      TEST_FAIL("[HttpHeaderMatch test setToHeader case5] ");
    }

    item = list->get(2);
    if(item == nullptr || !item->tag->equals("7892dd") || item->isWeakAlg) {
      TEST_FAIL("[HttpHeaderMatch test setToHeader case6] ");
    }
    break;
  }

  while(1) {
    HttpHeader header = createHttpHeader();
    header->set(createString("If-Match"),
                createString("*"));
    auto match = header->getIfMatch();
    
    ArrayList<HttpHeaderMatchItem> list = match->get();
    if(list->size() != 1){
      TEST_FAIL("[HttpHeaderMatch test setToHeader case7] ");
      break;
    }

    auto item = list->get(0);
    if(item == nullptr || !item->tag->equals("*") || item->isWeakAlg) {
      TEST_FAIL("[HttpHeaderMatch test setToHeader case8] ");
    }

    break;
  }

  TEST_OK("[HttpHeaderMatch test setToHeader case100]");
}