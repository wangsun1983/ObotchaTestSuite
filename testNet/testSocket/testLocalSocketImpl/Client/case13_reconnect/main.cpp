#include <signal.h>

#include "DatagramSocketImpl.hpp"
#include "SocketBuilder.hpp"
#include "SocketMonitor.hpp"
#include "Handler.hpp"
#include "InetLocalAddress.hpp"

#include "TestLog.hpp"
#include "NetEvent.hpp"

using namespace obotcha;

int main() {
    signal(SIGPIPE, SIG_IGN);
    InetAddress addr = InetLocalAddress::New("case1_socket");
    Socket client = SocketBuilder::New()->setAddress(addr)->newSocket();

    int ret = client->connect();
    if(ret != 0) {
        TEST_FAIL("TestLocalSocket Client case13_reconnect case1");
    }
    
    client->close();
    
    ret = client->connect();
    if(ret == 0) {
        TEST_FAIL("TestLocalSocket Client case13_reconnect case2");
    }
    
    //close python  server
    InetAddress addr2 = InetLocalAddress::New("case1_socket");
    Socket client2 = SocketBuilder::New()->setAddress(addr)->newSocket();
    int ret2 = client2->connect();
    String data = String::New("abcd");
    client2->getOutputStream()->write(data->toByteArray());
    client2->getOutputStream()->write(data->toByteArray());
    
    TEST_OK("TestLocalSocket Client case13_reconnect test3");
    return 0;
}