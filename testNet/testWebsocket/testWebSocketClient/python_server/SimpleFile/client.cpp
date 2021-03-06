#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Integer.hpp"
#include "StrongPointer.hpp"
#include "Long.hpp"
#include "WebSocketClient.hpp"
#include "WebSocketListener.hpp"
#include "File.hpp"
#include "FileInputStream.hpp"
#include "TestLog.hpp"
#include "NetPort.hpp"
#include "CountDownLatch.hpp"
#include "System.hpp"
#include "Md.hpp"
using namespace obotcha;

CountDownLatch latch = createCountDownLatch(1);

DECLARE_CLASS(MyWsListener) IMPLEMENTS(WebSocketListener) {
public:

    int onData(WebSocketFrame data) {
        String message = data->getData()->toString();
        if(!message->equals("i am server")) {
            TEST_FAIL("WebSocketClient SimpleConnect wrong response: %s",message->toChars());
        }

        latch->countDown();
        return 0;
    }

    int onConnect() {
        //printf("on connect fd \n");
        return 0;
    }

    int onDisconnect() {
        //printf("111111 on disconnect fd \n");
        return 0;
    }

    int onPong(String) {
        //printf("111111 onPong fd \n");
        return 0;
    }

    int onPing(String) {
        //printf("111111 onPing fd \n");
        return 0;
    }
};



int main() {
    File file = createFile("data");

    if(!file->exists()) {
      file->createNewFile();
        for(int i = 0;i<1024;i++) {
        FileOutputStream stream = createFileOutputStream(file);
        stream->open(st(OutputStream)::Append);
        String data = createString(st(System)::currentTimeMillis());
        for(int j = 0;j < 32;j++) {
          data = data->append(createString(st(System)::currentTimeMillis()));
        }
        stream->write(data->toByteArray());
        stream->close();
      }
    }

    MyWsListener l = createMyWsListener();
    WebSocketClient client = createWebSocketClient();
    int port = getEnvPort();
    String url = createString("ws://127.0.0.1:")->append(createString(port));
    client->connect(url,l);
    File f = createFile("data");
    client->sendFile(f);

    latch->await();

    Md md5sum = createMd();
    String base = md5sum->encrypt(createFile("data"));

    String newFile = md5sum->encrypt(createFile("./tmp/data"));

    if(!base->equals(newFile)) {
      TEST_FAIL("WebSocketClient SimpleConnect case100");
    }
    TEST_OK("WebSocketClient SimpleConnect case100");
}
