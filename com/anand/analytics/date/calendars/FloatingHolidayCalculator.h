#ifndef __FLOATING_HOLIDAY_CALC
#define __FLOATING_HOLIDAY_CALC

#include "../Day.h"
#include "../DayofWeek.h"
#include "../MonthYear.h"

namespace com {
    namespace anand {
        namespace analytics {
            namespace date {
                namespace calendars {
                    class FloatingHolidayCalculator {
                    private:
                        DayofWeek dayofWeek;
                        int month;
                        int numWeeks;
                        bool last;
                    public:
                        FloatingHolidayCalculator(DayofWeek dow, int m, int nw, bool l) : dayofWeek(dow), month (m), numWeeks (nw), last(l) {

                        }

                        Day get(int year) {
                            if (last) {
                                using namespace com::anand::analytics::date;
                                MonthYear monthYear(month, year);
                                Day lastDay(year, month, monthYear.getDaysInMonth());

                                while(lastDay.getDayOfWeek() != dayofWeek)
                                    lastDay--;

                                return lastDay;
                            } else {
                                //find the 1st day of the month
                                Day day(year, month, 1);
                                int weeksToAdd = numWeeks - 1;

                                day += (weeksToAdd * 7);
                                while (day.getDayOfWeek() != dayofWeek) {
                                    day++;
                                }
                                return day;
                            }

                        }
                    };
                }
            }
        }
    }
}

#endif
