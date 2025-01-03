#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "Runnable.hpp"
#include "Mutex.hpp"
#include "Condition.hpp"
#include "Integer.hpp"
#include "AutoLock.hpp"
#include "Mutex.hpp"
#include "System.hpp"

using namespace obotcha;

extern void testSpinlockLock();
extern void testSpinlockTryLock();
extern void testSpinlockTimeout();
extern void testSpinlockunLock();

int main() {
  testSpinlockunLock();
  testSpinlockTimeout();
  testSpinlockLock();
  testSpinlockTryLock();
  return 1;
}
