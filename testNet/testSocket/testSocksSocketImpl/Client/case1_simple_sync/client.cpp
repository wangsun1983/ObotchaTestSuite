#include "DatagramSocketImpl.hpp"
#include "SocketBuilder.hpp"
#include "SocketMonitor.hpp"
#include "Handler.hpp"
#include "Inet4Address.hpp"
#include "NetEvent.hpp"
#include "TestLog.hpp"
#include "NetPort.hpp"

using namespace obotcha;

int messageCount = 0;
int disconnectCount = 0;

Mutex disconnectMutex = createMutex();
Condition disconnectCond = createCondition();

String message = createString("");

DECLARE_CLASS(MyHandler) IMPLEMENTS(Handler) {
public:
  void handleMessage(sp<_Message> msg) {
    AutoLock l(disconnectMutex);
    disconnectCond->notify();
  }
};

MyHandler h = createMyHandler();

DECLARE_CLASS(MyListener) IMPLEMENTS(SocketListener){
public:
  void onSocketMessage(int event,Socket s,ByteArray data) {
    switch(event) {
      case st(NetEvent)::Message:
      //h->removeMessages(1);
      message = message->append(data->toString());
      messageCount++;
      //h->sendEmptyMessageDelayed(1,100);
      break;

      case st(NetEvent)::Disconnect:
      //disconnectCount++;
      AutoLock l(disconnectMutex);
      disconnectCond->notify();
      break;
    }
  }
};


int main() {
    int port = getEnvPort();
    InetAddress addr = createInet4Address(port);
    Socket client = createSocketBuilder()->setAddress(addr)->newSocket();

    int ret = client->connect();
    if(ret != 0) {
      TEST_FAIL("TestTcpSocket case1_simple_sync test1 connect");
      return 0;
    }

    String resp = createString("hello server");
    client->getOutputStream()->write(resp->toByteArray());

    SocketMonitor monitor = createSocketMonitor();
    int bindret = monitor->bind(client,createMyListener());
    AutoLock l(disconnectMutex);
    disconnectCond->wait(disconnectMutex);
    
    int count = message->counts(createString("hello server"));
    if(message->counts(createString("hello server")) != 50) {
      TEST_FAIL("TestTcpSocket case1_simple_sync test2  count is %d,message is %s",count,message->toChars());
    }

    client->close();
    monitor->close();

    port++;
    setEnvPort(port);

    monitor->close();
    TEST_OK("TestTcpSocket case1_simple_sync test3");
    return 0;
}