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
                    int month;
                    int yr;

                    Year year;

                public:
                    MonthYear(int m, int y) : month(m), yr(y), year(Year(yr)) {

                    }

                    inline int getDaysInMonth() {
                        if (year.isLeapYear())
                            return leapdays[month - 1];
                        else
                            return days[month - 1];

                    }
                };
            }
        }
    }
}

#endif