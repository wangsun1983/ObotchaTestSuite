#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "File.hpp"
#include "TestLog.hpp"
#include "FileInputStream.hpp"
#include "FileDescriptor.hpp"

using namespace obotcha;

void testFileOpen() {
    File f = createFile("./tmp/testOpen.txt");
    f->createNewFile();
    auto fd = f->open();
    if(fd == nullptr) {
        TEST_FAIL("[File Test {open()} case1]");
    }
    
    int _fd = fd->getFd();
    if(_fd <= 0) {
        TEST_FAIL("[File Test {open()} case2]");
    }
    
    char *p = "abcd";
    int ret = write(_fd,(const void *)p,4);
    if(ret != 4) {
        TEST_FAIL("[File Test {open()} case3]");
    }
    
    FileInputStream s = createFileInputStream(f);
    s->open();
    auto content = s->readAll();
    if(!content->toString()->equals("abcd")) {
        TEST_FAIL("[File Test {open()} case4]");
    }
    
    //static open file
    auto descriptor = st(File)::open("./tmp/testOpen2.txt",
                                    st(FileDescriptor)::ReadWriteOnly|st(FileDescriptor)::Create);
    if(descriptor == nullptr) {
        TEST_FAIL("[File Test {open()} case5]");
    }
    
    File f2 = createFile("./tmp/testOpen2.txt");
    if(!f2->exists()) {
        TEST_FAIL("[File Test {open()} case6]");
    }
    
    descriptor = st(File)::open("./tmp/testOpen3.txt");
    if(descriptor != nullptr) {
        TEST_FAIL("[File Test {open()} case7]");
    }
    TEST_OK("[File Test {open()} case100]");

}