#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Boolean.hpp"
#include "StrongPointer.hpp"
#include "IllegalArgumentException.hpp"
#include "NullPointerException.hpp"
#include "InitializeException.hpp"
#include "TestLog.hpp"

using namespace obotcha;

void testLogic() {

    //logicOr
    while(1) {
        //Test simple value
        Boolean t0 = createBoolean(true);
        t0->logicOr(true);
        if(!t0->toValue()) {
            TEST_FAIL("Boolean logicOr test1");
        }

        t0->logicOr(false);
        if(!t0->toValue()) {
            TEST_FAIL("Boolean logicOr test2");
        }

        t0 = createBoolean(false);
        t0->logicOr(true);
        if(!t0->toValue()) {
            TEST_FAIL("Boolean logicOr test3");
        }

        t0 = createBoolean(false);
        t0->logicOr(false);
        if(t0->toValue()) {
            TEST_FAIL("Boolean logicOr test4");
        }

        //Test class
        t0 = createBoolean(true);
        t0->logicOr(createBoolean(true));
        if(!t0->toValue()) {
            TEST_FAIL("Boolean logicOr test5");
        }

        t0->logicOr(createBoolean(false));
        if(!t0->toValue()) {
            TEST_FAIL("Boolean logicOr test6");
        }

        t0 = createBoolean(false);
        t0->logicOr(createBoolean(true));
        if(!t0->toValue()) {
            TEST_FAIL("Boolean logicOr test7");
        }

        t0 = createBoolean(false);
        t0->logicOr(createBoolean(false));
        if(t0->toValue()) {
            TEST_FAIL("Boolean logicOr test8");
        }

        TEST_OK("Boolean logicOr test9 ");
        break;
    }

    //logicAnd
    while(1) {
        //simple value
        Boolean t0 = createBoolean(true);
        t0->logicAnd(true);
        if(!t0->toValue()) {
            TEST_FAIL("Boolean logicAnd test1");
        }

        t0->logicAnd(false);
        if(t0->toValue()) {
            TEST_FAIL("Boolean logicAnd test2");
        }

        t0 = createBoolean(false);
        t0->logicAnd(true);
        if(t0->toValue()) {
            TEST_FAIL("Boolean logicAnd test3");
        }

        t0->logicOr(false);
        if(t0->toValue()) {
            TEST_FAIL("Boolean logicAnd test4");
        }

        //class data
        t0 = createBoolean(true);
        t0->logicAnd(createBoolean(true));
        if(!t0->toValue()) {
            TEST_FAIL("Boolean logicAnd test5");
        }

        t0->logicAnd(createBoolean(false));
        if(t0->toValue()) {
            TEST_FAIL("Boolean logicAnd test6");
        }

        t0 = createBoolean(false);
        t0->logicAnd(createBoolean(true));
        if(t0->toValue()) {
            TEST_FAIL("Boolean logicAnd test7");
        }

        t0->logicOr(createBoolean(false));
        if(t0->toValue()) {
            TEST_FAIL("Boolean logicAnd test8");
        }

        TEST_OK("Boolean logicAnd test9 ");
        break;
    }

}
