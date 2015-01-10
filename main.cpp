#include <iostream>
#include <map>

#include "com/anand/analytics/date/Day.h"
#include "com/anand/analytics/date/Year.h"
#include <boost/date_time/posix_time/posix_time.hpp>
#include "com/anand/analytics/date/calendars/FloatingHolidayCalculator.h"

#include <list>
using namespace std;

int main() {
    typedef com::anand::analytics::date::calendars::FloatingHolidayCalculator Calculator;
    typedef com::anand::analytics::date::DayofWeek DayofWeek;
    typedef boost::posix_time::ptime PTime;
    typedef boost::posix_time::microsec_clock Clock;
    typedef boost::posix_time::time_duration TimeDuration;

    PTime time_start(
            Clock::local_time()
    );

    int year = 2016;

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

    PTime time_end(
            Clock::local_time()
    );

    TimeDuration duration (time_end - time_start);
    std::cout << duration << std::endl;

    return 0;
}