#include <stdio.h>
#include <iostream>
#include <type_traits>

#include <string.h>
#include "String.hpp"
#include "ArrayList.hpp"
#include "NullPointerException.hpp"
#include "ArrayIndexOutOfBoundsException.hpp"
#include "IllegalArgumentException.hpp"
#include "TransformException.hpp"
#include "IllegalArgumentException.hpp"
#include "TestLog.hpp"

using namespace obotcha;

void TestStringUpdate() {

    /*
    void update(const char *);

    void update(const sp<_String> &str);

    void update(std::string);
    */
    while(1) {
        String str = String::New("abc");
        const char *q = "hello";
        str->update(q);

        if(!str->sameAs("hello")) {
            TEST_FAIL("String update test1");
            break;
        }

        String str2 = String::New("abc");
        char q2[16];
        memset(q2,0,16);
        q2[0] = '1';
        q2[1] = '2';
        q2[2] = '3';
        q2[3] = '4';
        q2[4] = '5';
        str2->update(q2);
        if(!str2->sameAs("12345")) {
            TEST_FAIL("String update test2");
            break;
        }

        q2[0] = '9';
        q2[1] = '9';
        q2[2] = '9';
        q2[3] = '9';
        q2[4] = '9';
        if(!str2->sameAs("12345")) {
            TEST_FAIL("String update test3");
            break;
        }

        String str3 = String::New("abc");
        str3->update("hhhh");
        if(!str3->sameAs("hhhh")) {
            TEST_FAIL("String update test4");
            break;
        }

        break;
    }

    while(1) {
        String str = String::New("abc");
        String str2 = String::New("ffff");
        str2->update(str);
        if(!str2->sameAs("abc")) {
            TEST_FAIL("String update test4");
            break;
        }

        str->update("ttt");
        if(!str2->sameAs("abc")) {
            TEST_FAIL("String update test5");
            break;
        }
        break;
    }

    while(1) {
        String str = String::New("abc");
        std::string str2 = "ffff";
        str->update(str2);

        if(!str->sameAs("ffff")) {
            TEST_FAIL("String update test6");
            break;
        }

        break;
    }
    TEST_OK("String update test100");
}
