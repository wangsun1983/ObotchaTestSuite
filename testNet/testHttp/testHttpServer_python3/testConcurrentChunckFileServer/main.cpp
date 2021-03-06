#include <stdio.h>
#include <unistd.h>
#include <signal.h>

#include "Handler.hpp"
#include "Message.hpp"
#include "System.hpp"
#include "ByteRingArray.hpp"
#include "HttpServer.hpp"
#include "HttpPacketWriter.hpp"
#include "HttpCookie.hpp"
#include "HttpResponse.hpp"
#include "HttpStatus.hpp"
#include "HttpServerBuilder.hpp"
#include "Inet4Address.hpp"
#include "CountDownLatch.hpp"
#include "Md.hpp"

#include "TestLog.hpp"
#include "NetPort.hpp"
#include "NetEvent.hpp"

using namespace obotcha;


CountDownLatch latch = createCountDownLatch(128*16);

DECLARE_CLASS(MyHttpListener) IMPLEMENTS(HttpListener) {


void onHttpMessage(int event,HttpLinker client,HttpResponseWriter w,HttpPacket msg){
    switch(event) {
        case st(NetEvent)::Connect: {
            //connectCount->incrementAndGet();
        }
        break;

        case st(NetEvent)::Message: {
            //messageCount->incrementAndGet();
            HttpResponse response = createHttpResponse();
            response->getHeader()->setResponseStatus(st(HttpStatus)::Ok);
            File file = createFile("data");
            response->getEntity()->setChunk(file);
            w->write(response);
            latch->countDown();
        }
        break;

        case st(NetEvent)::Disconnect:{
            //disConnectCount->incrementAndGet();
        }
        break;
    }
}

};

int main() {
  File file = createFile("data");
  long prepareFilesize = file->length();
  signal(SIGPIPE,SIG_IGN);

  if(!file->exists()) {
    file->createNewFile();
      for(int i = 0;i<128;i++) {
      FileOutputStream stream = createFileOutputStream(file);
      stream->open(st(OutputStream)::Append);
      String data = createString("");
      for(int j = 0;j < 32;j++) {
        data = data->append(createString(st(System)::currentTimeMillis()));
      }
      stream->write(data->toByteArray());
      stream->close();
    }
  }
  
  int port = getEnvPort();
  MyHttpListener listener = createMyHttpListener();
  HttpServer server = createHttpServerBuilder()
                    ->setAddress(createInet4Address(port))
                    ->setListener(listener)
                    ->build();
  server->start();
  latch->await();
  sleep(1);

  Md md5 = createMd();
  String base = md5->encrypt(createFile("data"));

  File tmpDir = createFile("./tmp");
  ArrayList<File> files = tmpDir->listFiles();
  if(files->size() != 128 *16) {
    TEST_FAIL("TestHttpServer testConcurrentChunckFileServer test1,download file num is %d",files->size());
  }

  auto iter = files->getIterator();
  while(iter->hasValue()) {
    auto f = iter->getValue();

    String v1 = md5->encrypt(f);
    if(!base->equals(v1)) {
      TEST_FAIL("TestHttpServer testConcurrentChunckFileServer test1,path is %s",f->getAbsolutePath()->toChars());
    }

    iter->next();
  }

  TEST_OK("TestHttpServer testConcurrentChunckFileServer test100");

  port++;
  setEnvPort(port);
  return 0;
}
