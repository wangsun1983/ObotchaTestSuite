#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "System.hpp"
#include "Barrier.hpp"
#include "ByteArrayReader.hpp"

using namespace obotcha;

extern void testLanguageParse();
extern void testLanguageToString();
extern void testSetToHeader();

int main() {
    testLanguageParse();
    testLanguageToString();
    testSetToHeader();
    return 0;
}
