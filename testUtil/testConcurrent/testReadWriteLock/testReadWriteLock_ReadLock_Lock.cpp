#include <stdio.h>
#include <unistd.h>

#include "ReadWriteLock.hpp"
#include "Runnable.hpp"
#include "Thread.hpp"
#include "System.hpp"
#include "AtomicInteger.hpp"
#include "TimeWatcher.hpp"
#include "TestLog.hpp"

using namespace obotcha;

void testReadLock_Lock() {
  TimeWatcher watcher = createTimeWatcher();

  while(1) {
    ReadWriteLock rwLock = createReadWriteLock();
    rwLock->getReadLock()->lock();
    AtomicInteger value = createAtomicInteger(0);
    Thread t = createThread([&value,&rwLock] {
        rwLock->getReadLock()->lock();
        value->incrementAndGet();
    });

    Thread t1 = createThread([&value,&rwLock] {
        rwLock->getReadLock()->lock();
        value->incrementAndGet();
    });

    Thread t2 = createThread([&value,&rwLock] {
        rwLock->getReadLock()->lock();
        value->incrementAndGet();
    });

    t->start();
    t1->start();
    t2->start();
    t->join();
    t1->join();
    t2->join();

    if(value->get() != 3) {
      TEST_FAIL("[TestReadLock ReadLock Lock case1]");
      break;
    }
    break;
  }

  while(1) {
    ReadWriteLock rwLock = createReadWriteLock();
    auto r1 = rwLock->getReadLock();
    auto r2 = rwLock->getReadLock();
    r1->lock();
    watcher->start();
    r2->lock();
    long v = watcher->stop();
    if(v > 5 || v < 0) {
      TEST_FAIL("[TestReadLock ReadLock Lock case2]");
      break;
    }
    break;
  }

  TEST_OK("[TestReadLock ReadLock Lock case100]");
}
