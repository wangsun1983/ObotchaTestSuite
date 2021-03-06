#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "HttpMime.hpp"
#include "HttpHeaderAcceptCh.hpp"
#include "HttpClient.hpp"
#include "HttpUrl.hpp"
#include "HttpPost.hpp"
#include "TestLog.hpp"
#include "System.hpp"
#include "NetPort.hpp"
#include "HttpMultiPart.hpp"
#include "Md.hpp"

using namespace obotcha;

void testMultipartContentRequest() {
  int port = getEnvPort();
  printf("port is %d \n",port);

  String url = createString("http://127.0.0.1:")->append(createString(port),"/test");
  HttpPost post = createHttpPost(url);

  HttpMultiPart multipart = createHttpMultiPart();
  //multipart->addFile(createFile("data"),createString("haha"));
  //multipart->addContent(createString("key1"),createString("value1"));
  multipart->addContent("tag1","value1");
  multipart->addContent("tag2","value2");
  multipart->addContent("tag3","value3");

  post->getEntity()->setMultiPart(multipart);

  HttpClient client = createHttpClient();
  HttpResponse response = client->execute(post);

  //check response
  ByteArray data = response->getEntity()->getContent();
  if(!data->toString()->equals("tag1value1tag2value2tag3value3")) {
    printf("data is %s \n",data->toString()->toChars());
    TEST_FAIL("testHttpClient testMultipartContentRequest case1");
  }

  //check file
  TEST_OK("testHttpClient testMultipartContentRequest case100");
}
