#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "Runnable.hpp"
#include "BlockingQueue.hpp"
#include "ExecutorBuilder.hpp"
#include "Integer.hpp"
#include "Future.hpp"
#include "System.hpp"
#include "Math.hpp"
#include "ExecutorResult.hpp"
#include "TestLog.hpp"

using namespace obotcha;

DECLARE_CLASS(MyResult) {
public:
  int value1;
  long value2;
};

DECLARE_CLASS(RunTestObject) IMPLEMENTS(Runnable) {
public:
    void run() {
        MyResult r = MyResult::New();
        r->value1 = 100;
        r->value2 = 123;
        st(ExecutorResult)::Set(r);
    }
};

DECLARE_CLASS(RunTestInt) IMPLEMENTS(Runnable) {
public:
    void run() {
        st(ExecutorResult)::Set(1);
    }
};

DECLARE_CLASS(RunTestByte) IMPLEMENTS(Runnable) {
public:
    void run() {
        st(ExecutorResult)::Set((byte)2);
    }
};

DECLARE_CLASS(RunTestDouble) IMPLEMENTS(Runnable) {
public:
    void run() {
        st(ExecutorResult)::Set(3.3);
    }
};

DECLARE_CLASS(RunTestBoolFalse) IMPLEMENTS(Runnable) {
public:
    void run() {
        st(ExecutorResult)::Set(false);
    }
};

DECLARE_CLASS(RunTestBoolTrue) IMPLEMENTS(Runnable) {
public:
    void run() {
        st(ExecutorResult)::Set(true);
    }
};


DECLARE_CLASS(RunTestLong) IMPLEMENTS(Runnable) {
public:
    void run() {
        st(ExecutorResult)::Set((long)400);
    }
};

DECLARE_CLASS(RunTestUint16) IMPLEMENTS(Runnable) {
public:
    void run() {
        st(ExecutorResult)::Set((uint16_t)5);
    }
};

DECLARE_CLASS(RunTestUint32) IMPLEMENTS(Runnable) {
public:
    void run() {
        st(ExecutorResult)::Set((uint32_t)6);
    }
};

DECLARE_CLASS(RunTestUint64) IMPLEMENTS(Runnable) {
public:
    void run() {
        st(ExecutorResult)::Set((uint64_t)7);
    }
};

DECLARE_CLASS(RunTestString) IMPLEMENTS(Runnable) {
public:
    void run() {
        st(ExecutorResult)::Set(String::New("hello world"));
    }
};

//delay Thread
DECLARE_CLASS(RunTestObjectDelayed) IMPLEMENTS(Runnable) {
public:
    void run() {
        MyResult r = MyResult::New();
        r->value1 = 100;
        r->value2 = 123;
        st(ExecutorResult)::Set(r);
        sleep(1);
    }
};

DECLARE_CLASS(RunTestIntDelayed) IMPLEMENTS(Runnable) {
public:
    void run() {
        st(ExecutorResult)::Set(1);
        sleep(1);
    }
};

DECLARE_CLASS(RunTestByteDelayed) IMPLEMENTS(Runnable) {
public:
    void run() {
        st(ExecutorResult)::Set((byte)2);
        sleep(1);
    }
};

DECLARE_CLASS(RunTestDoubleDelayed) IMPLEMENTS(Runnable) {
public:
    void run() {
        st(ExecutorResult)::Set(3.3);
        sleep(1);
    }
};

DECLARE_CLASS(RunTestBoolFalseDelayed) IMPLEMENTS(Runnable) {
public:
    void run() {
        st(ExecutorResult)::Set(false);
        sleep(1);
    }
};

DECLARE_CLASS(RunTestBoolTrueDelayed) IMPLEMENTS(Runnable) {
public:
    void run() {
        st(ExecutorResult)::Set(true);
        sleep(1);
    }
};


DECLARE_CLASS(RunTestLongDelayed) IMPLEMENTS(Runnable) {
public:
    void run() {
        st(ExecutorResult)::Set((long)400);
        sleep(1);
    }
};

DECLARE_CLASS(RunTestUint16Delayed) IMPLEMENTS(Runnable) {
public:
    void run() {
        st(ExecutorResult)::Set((uint16_t)5);
        sleep(1);
    }
};

DECLARE_CLASS(RunTestUint32Delayed) IMPLEMENTS(Runnable) {
public:
    void run() {
        st(ExecutorResult)::Set((uint32_t)6);
        sleep(1);
    }
};

DECLARE_CLASS(RunTestUint64Delayed) IMPLEMENTS(Runnable) {
public:
    void run() {
        st(ExecutorResult)::Set((uint64_t)7);
        sleep(1);
    }
};

DECLARE_CLASS(RunTestStringDelayed) IMPLEMENTS(Runnable) {
public:
    void run() {
        st(ExecutorResult)::Set(String::New("hello world"));
        sleep(1);
    }
};

DECLARE_CLASS(RunTestSleep10) IMPLEMENTS(Runnable) {
public:
    void run() {
        try {
          st(Thread)::Sleep(10*1000);
        } catch(...) {}

    }
};

void testThreadPoolExecutor_GetResult() {
  //simple test case1
  while(1) {
    auto pool = ExecutorBuilder::New()->newThreadPool();
    RunTestObject objRun = RunTestObject::New();
    Future f1 = pool->submit(objRun);
    MyResult r1 = f1->getResult<MyResult>();
    if(r1 == nullptr || r1->value1 != 100 || r1->value2 != 123) {
      TEST_FAIL("[Future ThreadPoolExecutor GetResult case1");
      break;
    }

    //int
    RunTestInt intRun = RunTestInt::New();
    Future f2 = pool->submit(intRun);
    int r2 = f2->getResult<int>();

    if(r2 != 1) {
      TEST_FAIL("[Future ThreadPoolExecutor GetResult case2");
      break;
    }

    //byte
    RunTestByte byteRun = RunTestByte::New();
    Future f3 = pool->submit(byteRun);
    byte r3 = f3->getResult<byte>();

    if(r3 != 2) {
      TEST_FAIL("[Future ThreadPoolExecutor GetResult case3");
      break;
    }

    //double
    RunTestDouble doubleRun = RunTestDouble::New();
    Future f4 = pool->submit(doubleRun);
    double r4 = f4->getResult<double>();

    if(r4 != 3.3) {
      TEST_FAIL("[Future ThreadPoolExecutor GetResult case4");
      break;
    }

    //bool false
    RunTestBoolFalse falseRun = RunTestBoolFalse::New();
    Future f5 = pool->submit(falseRun);
    bool r5 = f5->getResult<bool>();

    if(r5) {
      TEST_FAIL("[Future ThreadPoolExecutor GetResult case5");
      break;
    }

    //bool true
    RunTestBoolTrue trueRun = RunTestBoolTrue::New();
    Future f6 = pool->submit(trueRun);
    bool r6 = f6->getResult<bool>();

    if(!r6) {
      TEST_FAIL("[Future ThreadPoolExecutor GetResult case6");
      break;
    }

    //long
    RunTestLong longRun = RunTestLong::New();
    Future f7 = pool->submit(longRun);
    long r7 = f7->getResult<long>();

    if(r7 != 400) {
      TEST_FAIL("[Future ThreadPoolExecutor GetResult case7");
      break;
    }

    //uint16_t
    RunTestUint16 uint16Run = RunTestUint16::New();
    Future f8 = pool->submit(uint16Run);
    uint16_t r8 = f8->getResult<uint16_t>();

    if(r8 != 5) {
      TEST_FAIL("[Future ThreadPoolExecutor GetResult case8");
      break;
    }

    //uint32_t
    RunTestUint32 uint32Run = RunTestUint32::New();
    Future f9 = pool->submit(uint32Run);
    uint32_t r9 = f9->getResult<uint32_t>();

    if(r9 != 6) {
      TEST_FAIL("[Future ThreadPoolExecutor GetResult case9");
      break;
    }

    //uint64_t
    RunTestUint64 uint64Run = RunTestUint64::New();
    Future f10 = pool->submit(uint64Run);
    uint64_t r10 = f10->getResult<uint64_t>();

    if(r10 != 7) {
      TEST_FAIL("[Future ThreadPoolExecutor GetResult case10");
      break;
    }

    //String
    RunTestString stringRun = RunTestString::New();
    Future f11 = pool->submit(stringRun);
    String r11 = f11->getResult<String>();

    if(r11 == nullptr || !r11->sameAs("hello world")) {
      TEST_FAIL("[Future ThreadPoolExecutor GetResult case11");
      break;
    }

    pool->shutdown();

    TEST_OK("[Future ThreadPoolExecutor GetResult case12");
    break;
  }

  //simple test wait
  while(1) {
    auto pool = ExecutorBuilder::New()->newThreadPool();
    RunTestObjectDelayed objRun = RunTestObjectDelayed::New();
    Future f1 = pool->submit(objRun);
    long int start = st(System)::CurrentTimeMillis();
    MyResult r1 = f1->getResult<MyResult>();
    long int internal = st(System)::CurrentTimeMillis() - start;
    if(internal > 1005 || internal < 905) {
      TEST_FAIL("[Future ThreadPoolExecutor GetResult case13");
      break;
    }

    if(r1 == nullptr || r1->value1 != 100 || r1->value2 != 123) {
      TEST_FAIL("[Future ThreadPoolExecutor GetResult case14");
      break;
    }

    //int
    RunTestIntDelayed intRun = RunTestIntDelayed::New();
    Future f2 = pool->submit(intRun);
    //int r2 = f2->getResult<int>();
    start = st(System)::CurrentTimeMillis();
    int r2 = f2->getResult<int>();
    internal = st(System)::CurrentTimeMillis() - start;
    if(internal > 1005 || internal < 905) {
      TEST_FAIL("[Future ThreadPoolExecutor GetResult case15");
      break;
    }

    if(r2 != 1) {
      TEST_FAIL("[Future ThreadPoolExecutor GetResult case16");
      break;
    }

    //byte
    RunTestByteDelayed byteRun = RunTestByteDelayed::New();
    Future f3 = pool->submit(byteRun);
    //byte r3 = f3->getResult<byte>();
    start = st(System)::CurrentTimeMillis();
    byte r3 = f3->getResult<byte>();
    internal = st(System)::CurrentTimeMillis() - start;
    if(internal > 1005 || internal < 905) {
      TEST_FAIL("[Future ThreadPoolExecutor GetResult case17");
      break;
    }

    if(r3 != 2) {
      TEST_FAIL("[Future ThreadPoolExecutor GetResult case18");
      break;
    }

    //double
    RunTestDoubleDelayed doubleRun = RunTestDoubleDelayed::New();
    Future f4 = pool->submit(doubleRun);
    //double r4 = f4->getResult<double>();
    start = st(System)::CurrentTimeMillis();
    double r4 = f4->getResult<double>();
    internal = st(System)::CurrentTimeMillis() - start;
    if(internal > 1005 || internal < 905) {
      TEST_FAIL("[Future ThreadPoolExecutor GetResult case19");
      break;
    }

    if(r4 != 3.3) {
      TEST_FAIL("[Future ThreadPoolExecutor GetResult case20");
      break;
    }

    //bool false
    RunTestBoolFalseDelayed falseRun = RunTestBoolFalseDelayed::New();
    Future f5 = pool->submit(falseRun);
    //bool r5 = f5->getResult<bool>();
    start = st(System)::CurrentTimeMillis();
    bool r5 = f5->getResult<bool>();
    internal = st(System)::CurrentTimeMillis() - start;
    if(internal > 1005 || internal < 905) {
      TEST_FAIL("[Future ThreadPoolExecutor GetResult case21");
      break;
    }

    if(r5) {
      TEST_FAIL("[Future ThreadPoolExecutor GetResult case22");
      break;
    }

    //bool true
    RunTestBoolTrueDelayed trueRun = RunTestBoolTrueDelayed::New();
    Future f6 = pool->submit(trueRun);
    //bool r6 = f6->getResult<bool>();
    start = st(System)::CurrentTimeMillis();
    bool r6 = f6->getResult<bool>();
    internal = st(System)::CurrentTimeMillis() - start;
    if(internal > 1005 || internal < 905) {
      TEST_FAIL("[Future ThreadPoolExecutor GetResult case23");
      break;
    }

    if(!r6) {
      TEST_FAIL("[Future ThreadPoolExecutor GetResult case24");
      break;
    }

    //long
    RunTestLongDelayed longRun = RunTestLongDelayed::New();
    Future f7 = pool->submit(longRun);
    //long r7 = f7->getResult<long>();
    start = st(System)::CurrentTimeMillis();
    long r7 = f7->getResult<long>();
    internal = st(System)::CurrentTimeMillis() - start;
    if(internal > 1005 || internal < 905) {
      TEST_FAIL("[Future ThreadPoolExecutor GetResult case25");
      break;
    }

    if(r7 != 400) {
      TEST_FAIL("[Future ThreadPoolExecutor GetResult case26");
      break;
    }

    //uint16_t
    RunTestUint16Delayed uint16Run = RunTestUint16Delayed::New();
    Future f8 = pool->submit(uint16Run);
    //uint16_t r8 = f8->getResult<uint16_t>();
    start = st(System)::CurrentTimeMillis();
    uint16_t r8 = f8->getResult<uint16_t>();
    internal = st(System)::CurrentTimeMillis() - start;
    if(internal > 1005 || internal < 905) {
      TEST_FAIL("[Future ThreadPoolExecutor GetResult case27");
      break;
    }

    if(r8 != 5) {
      TEST_FAIL("[Future ThreadPoolExecutor GetResult case28");
      break;
    }

    //uint32_t
    RunTestUint32Delayed uint32Run = RunTestUint32Delayed::New();
    Future f9 = pool->submit(uint32Run);
    //uint32_t r9 = f9->getResult<uint32_t>();
    start = st(System)::CurrentTimeMillis();
    uint32_t r9 = f9->getResult<uint32_t>();
    internal = st(System)::CurrentTimeMillis() - start;
    if(internal > 1005 || internal < 905) {
      TEST_FAIL("[Future ThreadPoolExecutor GetResult case29");
      break;
    }

    if(r9 != 6) {
      TEST_FAIL("[Future ThreadPoolExecutor GetResult case30");
      break;
    }

    //uint64_t
    RunTestUint64Delayed uint64Run = RunTestUint64Delayed::New();
    Future f10 = pool->submit(uint64Run);
    //uint32_t r10 = f10->getResult<uint64_t>();
    start = st(System)::CurrentTimeMillis();
    uint64_t r10 = f10->getResult<uint64_t>();
    internal = st(System)::CurrentTimeMillis() - start;
    if(internal > 1005 || internal < 905) {
      TEST_FAIL("[Future ThreadPoolExecutor GetResult case31");
      break;
    }

    if(r10 != 7) {
      TEST_FAIL("[Future ThreadPoolExecutor GetResult case32");
      break;
    }

    //String
    RunTestStringDelayed stringRun = RunTestStringDelayed::New();
    Future f11 = pool->submit(stringRun);
    //String r11 = f11->getResult<String>();
    start = st(System)::CurrentTimeMillis();
    String r11 = f11->getResult<String>();
    internal = st(System)::CurrentTimeMillis() - start;
    if(internal > 1005 || internal < 905) {
      TEST_FAIL("[Future ThreadPoolExecutor GetResult case33");
      break;
    }

    if(r11 == nullptr || !r11->sameAs("hello world")) {
      TEST_FAIL("[Future ThreadPoolExecutor GetResult case34");
      break;
    }

    pool->shutdown();

    TEST_OK("[Future ThreadPoolExecutor GetResult case35");
    break;
  }

  //test cancel
  while(1) {
    auto pool = ExecutorBuilder::New()->setDefaultThreadNum(1)->newThreadPool();
    pool->submit(RunTestSleep10::New());
    bool isException = false;

    RunTestObject objRun = RunTestObject::New();
    Future f1 = pool->submit(objRun);
    Thread t = Thread::New([&f1]{
      usleep(100);
      f1->cancel();
    });
    t->start();

    try {
      MyResult r1 = f1->getResult<MyResult>();
    } catch(...) {
      isException = true;
    }

    if(!isException) {
      TEST_FAIL("[Future ThreadPoolExecutor GetResult case36");
      break;
    }

    //int
    RunTestInt intRun = RunTestInt::New();
    Future f2 = pool->submit(intRun);
    isException = false;
    t = Thread::New([&f2]{
      usleep(100);
      f2->cancel();
    });
    t->start();

    try {
      int r2 = f2->getResult<int>();
    } catch(...) {
      isException = true;
    }

    if(!isException) {
      TEST_FAIL("[Future ThreadPoolExecutor GetResult case37");
      break;
    }

    //byte
    RunTestByte byteRun = RunTestByte::New();
    Future f3 = pool->submit(byteRun);
    isException = false;
    t = Thread::New([&f3]{
      usleep(100);
      f3->cancel();
    });
    t->start();
    try {
      byte r3 = f3->getResult<byte>();
    } catch(...) {
      isException = true;
    }


    if(!isException) {
      TEST_FAIL("[Future ThreadPoolExecutor GetResult case38");
      break;
    }

    //double
    RunTestDouble doubleRun = RunTestDouble::New();
    Future f4 = pool->submit(doubleRun);
    //double r4 = f4->getResult<double>();
    isException = false;
    t = Thread::New([&f4]{
      usleep(100);
      f4->cancel();
    });
    t->start();
    try {
      double r4 = f4->getResult<double>();
    } catch(...) {
      isException = true;
    }

    if(!isException) {
      TEST_FAIL("[Future ThreadPoolExecutor GetResult case39");
      break;
    }

    //bool false
    RunTestBoolFalse falseRun = RunTestBoolFalse::New();
    Future f5 = pool->submit(falseRun);
    //bool r5 = f5->getResult<bool>();
    isException = false;
    t = Thread::New([&f5]{
      usleep(100);
      f5->cancel();
    });
    t->start();
    try {
      bool r5 = f5->getResult<bool>();
    } catch(...) {
      isException = true;
    }

    if(!isException) {
      TEST_FAIL("[Future ThreadPoolExecutor GetResult case40");
      break;
    }

    //bool true
    RunTestBoolTrue trueRun = RunTestBoolTrue::New();
    Future f6 = pool->submit(trueRun);
    //bool r6 = f6->getResult<bool>();
    isException = false;
    t = Thread::New([&f6]{
      usleep(100);
      f6->cancel();
    });
    t->start();
    try {
      bool r6 = f6->getResult<bool>();
    } catch(...) {
      isException = true;
    }

    if(!isException) {
      TEST_FAIL("[Future ThreadPoolExecutor GetResult case41");
      break;
    }

    //long
    RunTestLong longRun = RunTestLong::New();
    Future f7 = pool->submit(longRun);
    //long r7 = f7->getResult<long>();
    isException = false;
    t = Thread::New([&f7]{
      usleep(100);
      f7->cancel();
    });
    t->start();
    try {
      long r7 = f7->getResult<long>();
    } catch(...) {
      isException = true;
    }

    if(!isException) {
      TEST_FAIL("[Future ThreadPoolExecutor GetResult case42");
      break;
    }

    //uint16_t
    RunTestUint16 uint16Run = RunTestUint16::New();
    Future f8 = pool->submit(uint16Run);
    //uint16_t r8 = f8->getResult<uint16_t>();
    isException = false;
    t = Thread::New([&f8]{
      usleep(100);
      f8->cancel();
    });

    t->start();
    try {
      uint16_t r8 = f8->getResult<uint16_t>();
    } catch(...) {
      isException = true;
    }

    if(!isException) {
      TEST_FAIL("[Future ThreadPoolExecutor GetResult case43");
      break;
    }

    //uint32_t
    RunTestUint32 uint32Run = RunTestUint32::New();
    Future f9 = pool->submit(uint32Run);
    //uint32_t r9 = f9->getResult<uint32_t>();
    isException = false;
    t = Thread::New([&f9]{
      usleep(100);
      f9->cancel();
    });

    t->start();
    try {
      uint32_t r9 = f9->getResult<uint32_t>();
    } catch(...) {
      isException = true;
    }

    if(!isException) {
      TEST_FAIL("[Future ThreadPoolExecutor GetResult case44");
      break;
    }

    //uint64_t
    RunTestUint64 uint64Run = RunTestUint64::New();
    Future f10 = pool->submit(uint64Run);
    //uint64_t r10 = f10->getResult<uint64_t>();
    isException = false;
    t = Thread::New([&f10]{
      usleep(100);
      f10->cancel();
    });

    t->start();
    try {
      uint64_t r10 = f10->getResult<uint64_t>();
    } catch(...) {
      isException = true;
    }

    if(!isException) {
      TEST_FAIL("[Future ThreadPoolExecutor GetResult case45");
      break;
    }

    //String
    RunTestString stringRun = RunTestString::New();
    Future f11 = pool->submit(stringRun);
    //String r11 = f11->getResult<String>();
    isException = false;
    t = Thread::New([&f11]{
      usleep(100);
      f11->cancel();
    });

    t->start();
    try {
      String r11 = f11->getResult<String>();
    } catch(...) {
      isException = true;
    }

    if(!isException) {
      TEST_FAIL("[Future ThreadPoolExecutor GetResult case46");
      break;
    }
    pool->shutdown();
    pool->awaitTermination();

    TEST_OK("[Future ThreadPoolExecutor GetResult case47");
    break;
  }

  TEST_OK("[Future ThreadPoolExecutor GetResult case100");
}
