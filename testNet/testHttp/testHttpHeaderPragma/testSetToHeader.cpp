#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "HttpMime.hpp"
#include "HttpHeaderPragma.hpp"
#include "Math.hpp"
#include "TestLog.hpp"
#include "HttpHeader.hpp"

using namespace obotcha;

void testSetToHeader() {
  while(1) {
    HttpHeader header = createHttpHeader();
    header->set(createString("Pragma"),
                createString(" no-cache "));
    auto pragma = header->getPragma();
    if(!pragma->get()->equals("no-cache")){
      TEST_OK("[HttpHeaderPragma test setToHeader case1]");
      break;
    }
    break;
  }
  
  TEST_OK("[HttpHeaderPragma test setToHeader case100]");
}