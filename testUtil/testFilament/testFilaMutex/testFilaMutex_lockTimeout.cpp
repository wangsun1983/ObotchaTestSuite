#include <unistd.h>

#include "Filament.hpp"
#include "ArrayList.hpp"
#include "FilaRoutine.hpp"
#include "CountDownLatch.hpp"
#include "TestLog.hpp"
#include "Filament.hpp"
#include "TimeWatcher.hpp"
#include "Fila.hpp"

using namespace std;
using namespace obotcha;

void testFilaMutexLockTimeout() {
    while(1) {
		FilaRoutine c = FilaRoutine::New();
		c->start();
		FilaMutex mutex = FilaMutex::New();
		mutex->lock();
		
		c->execute([&]{
			TimeWatcher w = TimeWatcher::New();
			w->start();
			mutex->lock(100);
			auto r = w->stop();
			if(r < 95 || r > 105) {
				TEST_FAIL("FilaMutex test Lock Timeout case1");
			}
		});
		
		usleep(200*1000);
		mutex->unlock();
		c->execute([&]{
			TimeWatcher w = TimeWatcher::New();
			w->start();
			mutex->lock(100);
			auto r = w->stop();
			if(r > 5) {
				TEST_FAIL("FilaMutex test Lock Timeout case2");
			}
		});
		c->shutdown();
		c->awaitTermination();
		break;
	}
	
	while(1) {
		FilaRoutine c = FilaRoutine::New();
		c->start();
		FilaMutex mutex = FilaMutex::New();
		
		Thread t1 = Thread::New([&]{
			mutex->lock();
			usleep(1000*200);
			mutex->unlock();
		});
		t1->start();
		usleep(100*1000);
		
		c->execute([&]{
			TimeWatcher w = TimeWatcher::New();
			w->start();
			mutex->lock(100);
			auto r = w->stop();
			if(r > 105 || r < 95) {
				TEST_FAIL("FilaMutex test Lock Timeout case3,r is %d",r);
			}
		});
		usleep(1000*50);
		t1->join();
		c->shutdown();
		c->awaitTermination();
		break;
	}
	
	while(1) {
		FilaRoutine c = FilaRoutine::New();
		c->start();
		FilaMutex mutex = FilaMutex::New();
		c->execute([&]{
			mutex->lock();
			try {
				st(Fila)::Sleep(300);
				TEST_FAIL("FilaMutex test Lock Timeout case4");
			} catch(...) {}
			mutex->unlock();
		});
		usleep(1000*100);
		
		Thread t1 = Thread::New([&]{
			TimeWatcher w = TimeWatcher::New();
			w->start();
			mutex->lock(100);
			auto r = w->stop();
			if(r > 105 || r < 95) {
				TEST_FAIL("FilaMutex test Lock Timeout case5,r is %d",r);
			}
		});
		t1->start();
		t1->join();
		c->shutdown();
		c->awaitTermination();
		break;
	}
	
    TEST_OK("FilaMutex test Lock Timeout case100");
}
