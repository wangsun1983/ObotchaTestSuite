#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "File.hpp"
#include "TestLog.hpp"

using namespace obotcha;

void testFileGetName() {
    File file;
    String name;

    //test1
    file = File::New("Obotcha/test/testFile/abc.cpp");
    name = file->getName();
    if(name == nullptr || !name->sameAs("abc.cpp")) {
      TEST_FAIL("[File Test {getName()} case1],name is %s",name->toChars());
    }

    //test2
    file = File::New("Obotcha/test/testFile/abcdir/");
    name = file->getName();
    if(name == nullptr || !name->sameAs("abcdir")) {
      TEST_FAIL("[File Test {getName()} case2],name is %s",name->toChars());
    }
    //test3
    file = File::New("abc11.cpp");
    name = file->getName();
    if(name == nullptr || !name->sameAs("abc11.cpp")) {
      TEST_FAIL("[File Test {getName()} case3]");
    }

    //test4
    file = File::New("/");
    name = file->getName();
    if(name == nullptr || !name->sameAs("/")) {
      TEST_FAIL("[File Test {getName()} case4]");
    }

    //test5
    file = File::New("/a");
    name = file->getName();
    if(name == nullptr || !name->sameAs("a")) {
      TEST_FAIL("[File Test {getName()} case5]");
    }

    //test6
    file = File::New("a");
    name = file->getName();
    if(name == nullptr || !name->sameAs("a")) {
      TEST_FAIL("[File Test {getName()} case6]");
    }

    //test7
    file = File::New("a/c");
    name = file->getName();
    if(name == nullptr || !name->sameAs("c")) {
      TEST_FAIL("[File Test {getName()} case7]");
    }

    TEST_OK("[File Test {getName()} case100]");

}
