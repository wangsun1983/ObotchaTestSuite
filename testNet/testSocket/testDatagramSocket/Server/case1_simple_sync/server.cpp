#include "DatagramSocketImpl.hpp"
#include "SocketBuilder.hpp"
#include "SocketMonitor.hpp"
#include "Inet4Address.hpp"
#include "AutoLock.hpp"
#include "Condition.hpp"

#include "TestLog.hpp"
#include "NetEvent.hpp"
#include "NetPort.hpp"

using namespace obotcha;

String message = String::New("");
bool isFirst = true;

Mutex mMutex = Mutex::New();
Condition mCond = Condition::New();

DECLARE_CLASS(MyListener) IMPLEMENTS(SocketListener) {

public:
  void onSocketMessage(st(Net)::Event event,Socket s,ByteArray data) {
    printf("i received a message,event is %d \n",event);
    if(isFirst) {
      int len = s->getOutputStream()->write(String::New("hello client")->toByteArray());
      isFirst = false;
      printf("len is %d \n",len);
      mCond->notify();
      return;
    }

    message = message->append(data->toString());
  }

};

int main() {
  int port = getEnvPort();
  printf("port is %d \n",port);
  InetAddress addr = Inet4Address::New(port);
  Socket sock = SocketBuilder::New()->setAddress(addr)->newDatagramSocket();
  int result = sock->bind();
  printf("result is %d \n",result);
  SocketMonitor monitor = SocketMonitor::New();
  MyListener l = MyListener::New();
  monitor->bind(sock,l);
  printf("bind sock \n");
  AutoLock ll(mMutex);
  mCond->wait(mMutex);

  sleep(1);
  int count = message->counts("hello client");
  monitor->close();
  sock->close();
  if(message->counts("hello client") != 50) {
    TEST_FAIL("TestDataGramSocket Server case1_simple_sync test2 count is %d,message is %s",count,message->toChars());
  }

  port++;
  setEnvPort(port);
  TEST_OK("TestDataGramSocket Server case1_simple_sync test3");

}