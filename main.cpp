#include <iostream>
#include <map>

#include "com/anand/analytics/date/Day.h"
#include "com/anand/analytics/date/Year.h"
#include <boost/date_time/posix_time/posix_time.hpp>
#include "com/anand/analytics/date/calendars/FloatingHolidayCalculator.h"

#include <list>
using namespace std;

int main() {
    int yr = 2000;
    using namespace com::anand::analytics::date;


    int year = 2015;
    //Thanksgiving day
    typedef com::anand::analytics::date::calendars::FloatingHolidayCalculator Calculator;

    Calculator mlkDayCalc (DayofWeek::MON, 1, 3, false);
    Calculator presidentsDayCalc (DayofWeek::MON, 2, 3, false);
    Calculator memorialDayCalc (DayofWeek::MON, 5, 0, true);
    Calculator laborDayCalc (DayofWeek::MON, 9, 1, false);
    Calculator columbusDayCalc (DayofWeek::MON, 10, 2, false);
    Calculator thanksgivingDayCalc(DayofWeek::THU, 11, 4, false);

    list<Calculator> calculators;
    calculators.push_back(mlkDayCalc);
    calculators.push_back(presidentsDayCalc);
    calculators.push_back(memorialDayCalc);
    calculators.push_back(laborDayCalc);
    calculators.push_back(columbusDayCalc);
    calculators.push_back(thanksgivingDayCalc);

    for (std::list<Calculator>::iterator it = calculators.begin();
            it != calculators.end();
            it++) {
        std::cout << it->get(year) << std::endl;
    }


    /*
    using namespace boost::posix_time;
    ptime time_start(
            microsec_clock::local_time()
    );

    for (int i = 0; i < 30000; i++) {
        day++;

    }

    cout << day << endl;

    ptime time_end(
            microsec_clock::local_time()
    );
    time_duration duration (time_end - time_start);
    std::cout << duration << std::endl;
    */
    return 0;
}