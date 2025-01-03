#include <stdio.h>
#include <unistd.h>
#include <time.h>

#include "Calendar.hpp"
#include "File.hpp"
#include "FileInputStream.hpp"
#include "ArrayList.hpp"
#include "testCalendar.hpp"
#include "ForEveryOne.hpp"
#include "TextLineReader.hpp"
#include "Log.hpp"
#include "TestLog.hpp"

using namespace obotcha;

DECLARE_CLASS(DayTestItem) {
public:
    int year;
    int days;
};

void testCalendarGetDays() {
    TextLineReader input = TextLineReader::New(File::New("./testData/days.txt"));
    ArrayList<DayTestItem> items = ArrayList<DayTestItem>::New();
    while(1) {
        auto line = input->readLine();
        if(line == nullptr || line->size() == 0) {
            break;
        }
        
        ArrayList<String> values = line->split(" ");
        DayTestItem item = DayTestItem::New();
        item->year = values->get(0)->toInteger()->toValue();
        item->days = values->get(1)->toInteger()->toValue();
        items->add(item);
    }

    if(items->size() < 20) {
        TEST_FAIL("testCalendarGetDays case1");
    }
    
    ForEveryOne(item,items) {
        int year = item->year;
        int days = item->days;
        
        int _days = st(Calendar)::IsLeapYear(year)?366:365;
        if(days != _days) {
            TEST_FAIL("testCalendarGetDays case2,expect is %d,actual is %d",days,_days);
        }
    }
    
    TEST_OK("testCalendarGetDays case100");
}
