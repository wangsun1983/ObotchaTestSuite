#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "HttpMime.hpp"
#include "HttpHeaderRange.hpp"
#include "Math.hpp"
#include "TestLog.hpp"

using namespace obotcha;

void testParse() {
  while(1) {
    HttpHeaderRange range = HttpHeaderRange::New();
    range->load("bytes=200-1000, 2000-6576, 19000-");
    if(!range->getUnit()->sameAs("bytes")) {
      TEST_FAIL("[HttpHeaderRange test Parse case1]");
      break;
    }

    auto list = range->getRanges();
    if(list->size() != 3) {
      TEST_FAIL("[HttpHeaderRange test Parse case2]");
      break;
    }

    auto item0 = list->get(0);
    if(item0->rangeStart != 200) {
      TEST_FAIL("[HttpHeaderRange test Parse case3],item0->rangeStart is %d",item0->rangeStart);
      break;
    }

    if(item0->rangeEnd != 1000) {
      TEST_FAIL("[HttpHeaderRange test Parse case4]");
      break;
    }

    auto item1 = list->get(1);
    if(item1->rangeStart != 2000) {
      TEST_FAIL("[HttpHeaderRange test Parse case5]");
      break;
    }

    if(item1->rangeEnd != 6576) {
      TEST_FAIL("[HttpHeaderRange test Parse case6]");
      break;
    }

    auto item2 = list->get(2);
    if(item2->rangeStart != 19000) {
      TEST_FAIL("[HttpHeaderRange test Parse case7]");
      break;
    }

    if(item2->rangeEnd != -1) {
      TEST_FAIL("[HttpHeaderRange test Parse case8]");
      break;
    }

    break;
  }
  
  while(1) {
    HttpHeaderRange range = HttpHeaderRange::New();
    range->load("bytes=200-1000, 2000-6576, 19000-");
    if(!range->getUnit()->sameAs("bytes")) {
      TEST_FAIL("[HttpHeaderRange test Parse case9]");
      break;
    }

    auto list_0 = range->getRanges();
    
    HttpHeaderRange range2 = HttpHeaderRange::New();
    range2->setRanges(list_0);
    
    auto list = range2->getRanges();
    if(list->size() != 3) {
      TEST_FAIL("[HttpHeaderRange test Parse case10]");
      break;
    }

    auto item0 = list->get(0);
    if(item0->rangeStart != 200) {
      TEST_FAIL("[HttpHeaderRange test Parse case11],item0->rangeStart is %d",item0->rangeStart);
      break;
    }

    if(item0->rangeEnd != 1000) {
      TEST_FAIL("[HttpHeaderRange test Parse case12]");
      break;
    }

    auto item1 = list->get(1);
    if(item1->rangeStart != 2000) {
      TEST_FAIL("[HttpHeaderRange test Parse case13]");
      break;
    }

    if(item1->rangeEnd != 6576) {
      TEST_FAIL("[HttpHeaderRange test Parse case14]");
      break;
    }

    auto item2 = list->get(2);
    if(item2->rangeStart != 19000) {
      TEST_FAIL("[HttpHeaderRange test Parse case15]");
      break;
    }

    if(item2->rangeEnd != -1) {
      TEST_FAIL("[HttpHeaderRange test Parse case16]");
      break;
    }

    break;
  }
  
  TEST_OK("[HttpHeaderRange test Parse case100]");

}
