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
                        DayofWeek _dayofWeek;
                        int _month;
                        int _numWeeks;
                        bool _last;
                    public:
                        FloatingHolidayCalculator(DayofWeek dow, int m, int nw, bool l)
                                : _dayofWeek(dow), _month (m), _numWeeks (nw), _last(l) {

                        }

                        Day get(int year) {
                            if (_last) {
                                using namespace com::anand::analytics::date;
                                MonthYear monthYear(_month, year);
                                Day lastDay(year, _month, monthYear.getDaysInMonth());

                                while(lastDay.getDayOfWeek() != _dayofWeek)
                                    lastDay--;

                                return lastDay;
                            } else {
                                //find the 1st day of the month
                                Day day(year, _month, 1);
                                int weeksToAdd = _numWeeks - 1;

                                day += (weeksToAdd * 7);
                                while (day.getDayOfWeek() != _dayofWeek) {
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
