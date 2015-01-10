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
                    Day _startDay;
                    Day _endDay;
                    int _year;
                    bool _leap;

                public:
                    Year(int yr)  {
                        _year = yr;
                        int d1 = 1;
                        int d2 = 31;

                        int m1 = 1;
                        int m2 = 12;

                        _startDay = Day(_year, m1, d1);
                        _endDay = Day(_year, m2, d2);

                        _leap = isLeapYear();

                    }

                    inline bool isLeapYear() {
                        bool ret = false;
                        if (_year % 4 == 0) {
                            ret = true;
                        }
                        if (_year % 100 == 0) {
                            if (_year % 400 == 0)
                                ret = true;
                            else
                                ret = false;
                        }

                        return ret;
                    }

                    inline Day startDate() {
                        return _startDay;
                    }

                    inline Day endDate() {
                        return _endDay;
                    }

                    inline bool isLeap() {
                        return _leap;
                    }

                    friend ostream &operator<<(ostream &output,
                            Year &year) {
                        output << year.startDate() << " : " << year.endDate() << " : " << year.isLeap() << " : " << year.daysInYear();
                        return output;
                    }

                    inline Year operator+(int yrs) {
                        yrs += _year;
                        return Year(yrs);
                    }

                    inline Year operator+=(int yrs) {
                        _year += yrs;
                        *this = Year(_year);
                        return *this;
                    }

                    /**
                    * Postfix
                    */
                    inline
                    Year
                    operator++(int) {
                        Year currYear(_year);
                        _year++;
                        *this = Year(_year);
                        return currYear;
                    }

                    /**
                    * Prefix
                    */
                    inline
                    Year
                    operator++() {
                        _year++;
                        *this = Year(_year);
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