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
#include "Enviroment.hpp"
#include "Http2Server.hpp"
#include "NetEvent.hpp"
#include "TestLog.hpp"
#include "NetPort.hpp"
#include "NetProtocol.hpp"

using namespace obotcha;

// curl -v --http2 http://127.0.0.1:1234/aaa

// curl -v -d '12345abc' --http2 http://127.0.0.1:1234/aaa

//    curl -v -d '{"aps":{"alert":"Test Push","sound":"default"}}' \
    --cert /path/to/cert/cert.pem:SECURE_PASSWORD \
    -H "apns-topic: com.app.identifier" --http2 \
    https://api.development.push.apple.com/3/device/DEVICE_ID

CountDownLatch connectlatch = createCountDownLatch(128);
int step = 0;

DECLARE_CLASS(MyHttpListener) IMPLEMENTS(Http2Listener) {
  void onHttpMessage(int event,HttpLinker client,Http2ResponseWriter w,Http2Packet msg){
    
      switch(event) {
          case st(NetEvent)::Connect: {
              
          }
          break;

          case st(NetEvent)::Message: {
                if(step == 0) {
                    HttpResponse response = createHttpResponse();
                    auto hh = response->getHeader();
                    printf("hh addr is %lx \n",hh.get_pointer());
                    //response->getHeader()->set(createString("mytest1"),createString("myvalue1"));
                    //response->getHeader()->set(createString("mytest2"),createString("myvalue2"));
                    response->getHeader()->setResponseStatus(st(HttpStatus)::Ok);
                    response->getEntity()->setContent(createString("hello this is server")->toByteArray());
                    w->write(response);
                } else {
                    usleep(1000*10);
                    String value = msg->getData()->toString();
                    printf("value is %s \n",value->toChars());
                }
                
          }
          break;

          case st(NetEvent)::Disconnect:{
          }
          break;
      }
      
  }
};

int main() {
  int port = getEnvPort();
  MyHttpListener listener = createMyHttpListener();
  Http2Server server = createHttpServerBuilder()
                    ->setAddress(createInet4Address(port))
                    ->setHttp2Listener(listener)
                    ->buildHttp2Server();
  server->start();
  connectlatch->await();
  server->close();
  usleep(1000*100);
  port++;
  setEnvPort(port);
  TEST_OK("TestHttp2Server SimpleConnect test100");

  return 0;
}