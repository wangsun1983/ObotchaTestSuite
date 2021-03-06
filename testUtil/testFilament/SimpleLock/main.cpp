#include <unistd.h>

#include "Filament.hpp"
#include "ArrayList.hpp"
#include "FilaRoutine.hpp"
#include "CountDownLatch.hpp"
#include "TestLog.hpp"
#include "Filament.hpp"
#include "TimeWatcher.hpp"

using namespace std;
using namespace obotcha;

extern void testSimpleLock();
extern void testRoutineLock();
extern void testAutoLock();
extern void testRoutineLockInThread();

int main() {
  testAutoLock();
  testSimpleLock();
  testRoutineLock();
  testRoutineLockInThread();
  return 0;
}
