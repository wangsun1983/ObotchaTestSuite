#include <stdio.h>
#include <unistd.h>

#include "Object.hpp"
#include "Exception.hpp"
#include "TestLog.hpp"

using namespace obotcha;

DECLARE_EXCEPTION(MyException) {
public:
    MyException(const char * str):Exception(str){

    }
    MyException(String str):Exception(str) {}
};


void doException() {
    String exception = createString("ByteArray [] fail")
                            ->append("size is",
                                    createString(1),
                                    "index is ",
                                    createString(1));
    Trigger(MyException,exception);
}


int main() {
    bool isException = false;

    try {
        doException();
    }catch(MyException e) {
        isException = true;
    }

    if(!isException) {
        TEST_FAIL("---[Exception test1]");
    }

    TEST_OK("---[Exception test1]");
    return 1;
}
