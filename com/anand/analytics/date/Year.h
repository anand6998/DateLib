#ifndef __YEAR_H
#define __YEAR_H

#include "Day.h"
#include "DateRange.h"
#include <ostream>

using namespace std;

namespace com {
    namespace anand {
        namespace analytics {
            namespace date {
                class Year : public DateRange {
                private:
                    Day stDay;
                    Day endDay;

                    int _thisyear;

                    bool leap;
                public:
                    Year(int yr)  {
                        _thisyear = yr;
                        int d1 = 1;
                        int d2 = 31;

                        int m1 = 1;
                        int m2 = 12;

                        stDay = Day(_thisyear, m1, d1);
                        endDay = Day(_thisyear, m2, d2);

                        leap = isLeapYear();

                    }

                    bool isLeapYear() {
                        bool ret = false;
                        if (_thisyear % 4 == 0) {
                            ret = true;
                        }
                        if (_thisyear % 100 == 0) {
                            if (_thisyear % 400 == 0)
                                ret = true;
                            else
                                ret = false;
                        }

                        return ret;
                    }

                    Day startDate() {
                        return stDay;
                    }

                    Day endDate() {
                        return endDay;
                    }

                    bool isLeap() {
                        return leap;
                    }

                    friend ostream &operator<<(ostream &output,
                            Year &year) {
                        output << year.startDate() << " : " << year.endDate() << " : " << year.isLeap() << " : " << year.daysInYear();
                        return output;
                    }

                    inline Year operator+(int yrs) {
                        yrs += _thisyear;
                        return Year(yrs);
                    }

                    inline Year operator+=(int yrs) {
                        _thisyear += yrs;
                        *this = Year(_thisyear);
                        return *this;
                    }

                    /**
                    * Postfix
                    */
                    inline
                    Year
                    operator++(int) {
                        Year currYear(_thisyear);
                        _thisyear++;
                        *this = Year(_thisyear);
                        return currYear;
                    }

                    /**
                    * Prefix
                    */
                    inline
                    Year
                    operator++() {
                        _thisyear++;
                        *this = Year(_thisyear);
                        return *this;
                    }

                    inline int
                    daysInYear() {
                        return (endDate() - startDate() + 1);
                    }

                };
            }

        }
    }
}

#endif