#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <memory.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "ByteArray.hpp"
#include "StrongPointer.hpp"
#include "ArrayIndexOutOfBoundsException.hpp"
#include "DateTime.hpp"
#include "Calendar.hpp"
#include "TestLog.hpp"

using namespace obotcha;


void testISO8601() {
    DateTime dt = createDateTime(2005, st(Calendar)::January, 8, 12, 30, 00);

    String str = dt->toString(st(DateTime)::FormatISO8601);
    if(!str->equals(createString("2005-01-08T12:30:00Z"))) {
        TEST_FAIL("DateTime toString ISO8601 test1");
        return;
    }

    str =  dt->toStringWithTimeZone(st(DateTime)::FormatISO8601, 3600);
    if(!str->equals(createString("2005-01-08T12:30:00+01:00"))) {
        TEST_FAIL("DateTime toString ISO8601 test2");
        return;
    }

    str = dt->toStringWithTimeZone(st(DateTime)::FormatISO8601, -3600);
    if(!str->equals(createString("2005-01-08T12:30:00-01:00"))) {
        TEST_FAIL("DateTime toString ISO8601 test2");
        return;
    }

    TEST_OK("DateTime toString ISO8601 test3");
}


void testISO8601Frac() {
    DateTime dt = createDateTime(2005, st(Calendar)::January, 8, 12, 30, 00, 12, 34);
    String str = dt->toString(st(DateTime)::FormatISO8601Frac);
    if(!str->equals(createString("2005-01-08T12:30:00.012034Z"))) {
        TEST_FAIL("DateTime toString ISO8601Frac test1");
        return;
    }

    str = dt->toStringWithTimeZone(st(DateTime)::FormatISO8601Frac, 3600);
    if(!str->equals(createString("2005-01-08T12:30:00.012034+01:00"))) {
        TEST_FAIL("DateTime toString ISO8601Frac test2");
        return;
    }

    str = dt->toStringWithTimeZone(st(DateTime)::FormatISO8601Frac, -3600);
    if(!str->equals(createString("2005-01-08T12:30:00.012034-01:00"))) {
        TEST_FAIL("DateTime toString ISO8601Frac test3");
        return;
    }
    TEST_OK("DateTime toString ISO8601Frac");
}


void testRFC822() {
    DateTime dt = createDateTime(2005, st(Calendar)::January, 8, 12, 30, 00);
    String str = dt->toString(st(DateTime)::FormatRFC822);
    if(!str->equals(createString("Sat, 8 Jan 05 12:30:00 GMT"))) {
        TEST_FAIL("DateTime toString RFC822 test1");
        return;
    }

    str = dt->toStringWithTimeZone(st(DateTime)::FormatRFC822, 3600);
    if(!str->equals(createString("Sat, 8 Jan 05 12:30:00 +0100"))) {
        TEST_FAIL("DateTime toString RFC822 test2");
        return;
    }

    str = dt->toStringWithTimeZone(st(DateTime)::FormatRFC822, -3600);
    if(!str->equals(createString("Sat, 8 Jan 05 12:30:00 -0100"))) {
        TEST_FAIL("DateTime toString RFC822 test3");
        return;
    }

    TEST_OK("DateTime toString RFC822 test4");

}

void testRFC1123() {
    DateTime dt = createDateTime(2005, st(Calendar)::January, 8, 12, 30, 00);
    String str = dt->toString(st(DateTime)::FormatRFC1123);
    if(!str->equals(createString("Sat, 8 Jan 2005 12:30:00 GMT"))) {
        TEST_FAIL("DateTime toString RFC1123 test1");
        return;
    }

    str = dt->toStringWithTimeZone(st(DateTime)::FormatRFC1123, 3600);
    if(!str->equals(createString("Sat, 8 Jan 2005 12:30:00 +0100"))) {
        TEST_FAIL("DateTime toString RFC1123 test2");
        return;
    }

    str = dt->toStringWithTimeZone(st(DateTime)::FormatRFC1123, -3600);
    if(!str->equals(createString("Sat, 8 Jan 2005 12:30:00 -0100"))) {
        TEST_FAIL("DateTime toString RFC1123 test3");
        return;
    }

    TEST_OK("DateTime toString RFC1123 test4");
}


void testHTTP() {
    DateTime dt = createDateTime(2005, st(Calendar)::January, 8, 12, 30, 00);

    String str = dt->toString(st(DateTime)::FormatHTTP);
    if(!str->equals(createString("Sat, 08 Jan 2005 12:30:00 GMT"))) {
        TEST_FAIL("DateTime toString Http test1");
        return;
    }

    str = dt->toStringWithTimeZone(st(DateTime)::FormatHTTP, 3600);
    if(!str->equals(createString("Sat, 08 Jan 2005 12:30:00 +0100"))) {
        TEST_FAIL("DateTime toString Http test2");
        return;
    }

    str = dt->toStringWithTimeZone(st(DateTime)::FormatHTTP, -3600);
    if(!str->equals(createString("Sat, 08 Jan 2005 12:30:00 -0100"))) {
        TEST_FAIL("DateTime toString Http test3");
        return;
    }

    TEST_OK("DateTime toString Http test4");
}


void testRFC850() {
    DateTime dt = createDateTime(2005, st(Calendar)::January, 8, 12, 30, 00);

    String str = dt->toString(st(DateTime)::FormatRFC850);
    if(!str->equals(createString("Saturday, 8-Jan-05 12:30:00 GMT"))) {
        TEST_FAIL("DateTime toString RFC850 test1");
        return;
    }

    str = dt->toStringWithTimeZone(st(DateTime)::FormatRFC850, 3600);
    if(!str->equals(createString("Saturday, 8-Jan-05 12:30:00 +0100"))) {
        TEST_FAIL("DateTime toString RFC850 test2");
        return;
    }

    str = dt->toStringWithTimeZone(st(DateTime)::FormatRFC850, -3600);
    if(!str->equals(createString("Saturday, 8-Jan-05 12:30:00 -0100"))) {
        TEST_FAIL("DateTime toString RFC850 test3");
        return;
    }

    TEST_OK("DateTime toString RFC850 test4");

}


void testRFC1036() {
    DateTime dt = createDateTime(2005, st(Calendar)::January, 8, 12, 30, 00);

    String str = dt->toString(st(DateTime)::FormatRFC1036);
    if(!str->equals(createString("Saturday, 8 Jan 05 12:30:00 GMT"))) {
        TEST_FAIL("DateTime toString RFC1036 test1");
        return;
    }

    str = dt->toStringWithTimeZone(st(DateTime)::FormatRFC1036, 3600);
    if(!str->equals(createString("Saturday, 8 Jan 05 12:30:00 +0100"))) {
        TEST_FAIL("DateTime toString RFC1036 test2");
        return;
    }

    str = dt->toStringWithTimeZone(st(DateTime)::FormatRFC1036, -3600);
    if(!str->equals(createString("Saturday, 8 Jan 05 12:30:00 -0100"))) {
        TEST_FAIL("DateTime toString RFC1036 test3");
        return;
    }
    TEST_OK("DateTime toString RFC1036 test4");

}


void testASCTIME()
{
    DateTime dt = createDateTime(2005, st(Calendar)::January, 8, 12, 30, 00);

    String str = dt->toString(st(DateTime)::FormatASCTIME);
    if(!str->equals(createString("Sat Jan  8 12:30:00 2005"))) {
        TEST_FAIL("DateTime toString ASCTIME test1");
        return;
    }

    TEST_OK("DateTime toString ASCTIME test2");
}


void testSORTABLE()
{
    DateTime dt = createDateTime(2005, st(Calendar)::January, 8, 12, 30, 00);

    String str = dt->toString(st(DateTime)::FormatSORTABLE);
    if(!str->equals(createString("2005-01-08 12:30:00"))) {
        TEST_FAIL("DateTime toString SORTABLE test1");
        return;
    }
    TEST_OK("DateTime toString SORTABLE test2");
}


void testCustom()
{
  DateTime dt = createDateTime(2005, st(Calendar)::January, 8, 12, 30, 00, 250);

    String str = dt->toString(createString("%w/%W/%b/%B/%d/%e/%f/%m/%n/%o/%y/%Y/%H/%h/%a/%A/%M/%S/%i/%c/%z/%Z/%%"));
    if(!str->equals(createString("Sat/Saturday/Jan/January/08/8/ 8/01/1/ 1/05/2005/12/12/pm/PM/30/00/250/2/Z/GMT/%"))) {
        printf("str is %s \n",str->toChars());
        printf("Sat/Saturday/Jan/January/08/8/ 8/01/1/ 1/05/2005/12/12/pm/PM/30/00/250/2/Z/GMT/ \n");

        TEST_FAIL("DateTime toString Custom test1");
        return;
    }

    TEST_OK("DateTime toString Custom test2");

}

void tostringtest() {
    testISO8601();
    testISO8601Frac();
    testRFC822();
    testRFC1123();
    testHTTP();
    testRFC850();
    testRFC1036();
    testASCTIME();
    testSORTABLE();
    testCustom();
}
