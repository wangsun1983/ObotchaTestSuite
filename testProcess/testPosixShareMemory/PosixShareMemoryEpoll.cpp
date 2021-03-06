#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "StrongPointer.hpp"
#include "PosixShareMemory.hpp"
#include "EPollFileObserver.hpp"

using namespace obotcha;

//do not support ????
void testPosixShareMemoryEpoll() {
  PosixShareMemory memory = createPosixShareMemory("shareMemoryabc1122",32,st(PosixShareMemory)::WriteRead);
  EPollFileObserver mPoll = createEPollFileObserver();
  printf("channel is %d \n",memory->getChannel());
  mPoll->addObserver(
    memory->getChannel(), EPOLLIN | EPOLLRDHUP | EPOLLHUP,
    [](int fd, uint32_t events) {
          if(events&EPOLLIN != 0) {
              printf("i get a value \n");
          }
          return 0;
    });
  
  memory->write(createString("hello")->toByteArray());
  sleep(1);
}
