#ifndef __MONTHYEAR_
#define __MONTHYEAR_

#include "Year.h"


namespace com {
    namespace anand {
        namespace analytics {
            namespace date {

                static int days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
                static int leapdays[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

                class MonthYear {

                private:
                    int _month;
                    int _yr;

                    Year _year;

                public:
                    MonthYear(int m, int y) : _month(m), _yr(y), _year(Year(_yr)) {

                    }

                    inline int getDaysInMonth() {
                        if (_year.isLeapYear())
                            return leapdays[_month - 1];
                        else
                            return days[_month - 1];

                    }
                };
            }
        }
    }
}

#endif