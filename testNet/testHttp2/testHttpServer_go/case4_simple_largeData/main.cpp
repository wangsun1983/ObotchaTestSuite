#include <stdio.h>
#include <unistd.h>

#include "Handler.hpp"
#include "Message.hpp"
#include "System.hpp"
#include "ByteRingArray.hpp"
#include "HttpServer.hpp"
#include "HttpCookie.hpp"
#include "HttpResponse.hpp"
#include "HttpStatus.hpp"
#include "HttpServerBuilder.hpp"
#include "Inet4Address.hpp"
#include "CountDownLatch.hpp"
#include "Handler.hpp"
#include "HttpPacketWriter.hpp"
#include "Http2Server.hpp"
#include "NetEvent.hpp"
#include "TestLog.hpp"
#include "NetPort.hpp"
#include "Net.hpp"

using namespace obotcha;

// curl -v --http2 http://127.0.0.1:1234/aaa

// curl -v -d '12345abc' --http2 http://127.0.0.1:1234/aaa

//    curl -v -d '{"aps":{"alert":"Test Push","sound":"default"}}' \
    --cert /path/to/cert/cert.pem:SECURE_PASSWORD \
    -H "apns-topic: com.app.identifier" --http2 \
    https://api.development.push.apple.com/3/device/DEVICE_ID

CountDownLatch connectlatch = CountDownLatch::New(1);
int step = 0;
long size = 0;

ByteArray acceptData = nullptr;

DECLARE_CLASS(MyHttpListener) IMPLEMENTS(Http2Listener) {
  void onHttpMessage(st(Net)::Event event,HttpLinker client,Http2ResponseWriter w,Http2Packet msg){
    
      switch(event) {
          case st(Net)::Event::Connect: {
              
          }
          break;

          case st(Net)::Event::Message: {
                // if(acceptData == nullptr) {
                //     acceptData = msg->getEntity()->getContent();
                // } else {
                //     acceptData->append(msg->getEntity()->getContent());
                // }
                //printf("accept total size is %ld \n",acceptData->size());
                acceptData = msg->getEntity()->getContent();
                //if(acceptData->size() >= 1024*1024*2) {
                    HttpResponse response = HttpResponse::New();
                    response->getHeader()->setResponseStatus(st(HttpStatus)::Ok);
                    response->getEntity()->setContent(String::New("hello this is server")->toByteArray());
                    w->write(response);
                    connectlatch->countDown();
                //}
          }
          break;

          case st(Net)::Event::Disconnect:{
          }
          break;
      }
      
  }
};

int main() {
  int port = getEnvPort();
  printf("server port is %d \n",port);
  MyHttpListener listener = MyHttpListener::New();
  Http2Server server = HttpServerBuilder::New()
                    ->setAddress(Inet4Address::New(8080))
                    ->setHttp2Listener(listener)
                    ->buildHttp2Server();
  server->start();
  connectlatch->await();
  server->close();
  usleep(1000*100);
  
  if(acceptData->size() != 1024*1024*4) {
      TEST_FAIL("TestHttp2Server Simple Large data test1,data size is %ld",acceptData->size());
  }
  
  for(int i = 0;i < 1024*1024*4;i++) {
        if(acceptData[i] != i%32) {
            TEST_FAIL("TestHttp2Server Simple Large data test2, index is %d,value is %d,expected is %d",
                    i,acceptData[i],i%32);
        }
  }
  port++;
  setEnvPort(port);
  TEST_OK("TestHttp2Server Simple Large data test100");

  return 0;
}
