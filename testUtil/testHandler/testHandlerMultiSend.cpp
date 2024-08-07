#include <stdio.h>
#include <unistd.h>

#include "Handler.hpp"
#include "Message.hpp"
#include "System.hpp"
#include "TestLog.hpp"

using namespace obotcha;

DECLARE_CLASS(MyMultiHandler1) IMPLEMENTS(Handler) {
public:
  _MyMultiHandler1() {
    count = 0;
  }

  void handleMessage(Message msg) {
      //TEST_FAIL("msg arg1 is %d \n",msg->arg1);
      count++;
  }

  int count;
};

MyMultiHandler1 mulitHandler = MyMultiHandler1::New();

DECLARE_CLASS(SendThread) IMPLEMENTS(Thread) {
public:
  void run() {
    for(int index = 0;index<1024*5;index++) {
      Message msg = Message::New(1);
      msg->arg1 = index;
      mulitHandler->sendMessage(msg);
    }
  }
};

void testHandlerMultiSend() {
  //case 1
  while(1) {
    SendThread t1 = SendThread::New();
    SendThread t2 = SendThread::New();
    SendThread t3 = SendThread::New();
    SendThread t4 = SendThread::New();
    SendThread t5 = SendThread::New();
    t1->start();
    t2->start();
    t3->start();
    t4->start();
    t5->start();

    t1->join();
    t2->join();
    t3->join();
    t4->join();
    t5->join();
    sleep(10);
    if(mulitHandler->count != 1024*5*5) {
      TEST_FAIL("[Handler Test {MultiSend} case1],mulitHandler->count is %d \n",mulitHandler->count);
      break;
    }

    TEST_OK("[Handler Test {MultiSend} case2]");
    break;
  }

  TEST_OK("[Handler Test {MultiSend} case3]");
}
