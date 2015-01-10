#ifndef _DAY_H
#define _DAY_H

#include "DayofWeek.h"
#include <boost/date_time/gregorian/gregorian_types.hpp>
#include <boost/lexical_cast.hpp>

#include <ostream>

using namespace std;

namespace com {
    namespace anand {
        namespace analytics {
            namespace date {
                class Day {
                private:
                    int _dayOfMonth;
                    int _monthOfYear;
                    int _year;
                    
                    int _jdn;
                    DayofWeek _dayOfWeek;

                public:
                    int get_dayOfMonth() const {
                        return _dayOfMonth;
                    }

                    int get_monthOfYear() const {
                        return _monthOfYear;
                    }

                    int getYear() const {
                        return _year;
                    }
                    
                    DayofWeek getDayOfWeek() {
                        return _dayOfWeek;
                    }

                private:
                    int compute(int _d, int _m, int _y) {
                        int a = (14 - _m) / 12;
                        int y = _y + 4800 - a;
                        int m = _m + 12 * a - 3;

                        int value = _d + (153 * m + 2) / 5 + 365 * y + y / 4 - y / 100 + y / 400 - 32045;
                        //this->_jdn = value;
                        return value;
                    }

                    DayofWeek computeDayOfWeek(int _jdn) {
                        int iDow = (_jdn + 1) % 7;
                        DayofWeek dow = static_cast<DayofWeek> (iDow);
                        return dow;
                    }

                public:
                    Day() {

                        boost::gregorian::date d(
                                boost::gregorian::day_clock::local_day()
                        );

                        _dayOfMonth = d.day();
                        _monthOfYear = d.month();
                        _year = d.year();

                        _jdn = compute(_dayOfMonth, _monthOfYear, _year);
                        _dayOfWeek = computeDayOfWeek(_jdn);
                    }

                    Day(int y, int m, int d) : _dayOfMonth(d), _monthOfYear(m), _year(y) {
                        _jdn = compute(_dayOfMonth, _monthOfYear, _year);
                        _dayOfWeek = computeDayOfWeek(_jdn);
                    }

                    Day(const Day &other) {
                        _dayOfMonth = other._dayOfMonth;
                        _monthOfYear = other._monthOfYear;
                        _year = other._year;
                        _jdn = other._jdn;
                        _dayOfWeek = other._dayOfWeek;
                    }

                    Day(int J) {

                        int y = 4716;
                        int j = 1401;
                        int m = 2;
                        int n = 12;
                        int r = 4;
                        int p = 1461;
                        int v = 3;
                        int u = 5;
                        int s = 153;
                        int w = 2;
                        int B = 274277;
                        int C = -38;

                        int f = J + j + (((4 * J + B) / 146097) * 3) / 4 + C;
                        int e = r * f + v;
                        int g = (e % p) / r;
                        int h = u * g + w;

                        int D = (h % s) / u + 1;
                        int M = (h / s + m) % n + 1;
                        int Y = (e / p ) - y + ( n + m - M ) / n;

                        _dayOfMonth = D;
                        _monthOfYear = M;
                        _year = Y;
                        _jdn = J;
                        _dayOfWeek = computeDayOfWeek(_jdn);
                    }

                    Day& operator=(const Day &other) {
                        _dayOfMonth = other._dayOfMonth;
                        _monthOfYear = other._monthOfYear;
                        _year = other._year;

                        _jdn = other._jdn;
                        _dayOfWeek = other._dayOfWeek;
                        return *this;
                    }

                    friend ostream& operator<<(ostream &output,
                            const Day &day) {
                        std::string strDay = boost::lexical_cast<std::string>(day._dayOfMonth);
                        if (day._dayOfMonth < 10)
                            strDay = "0" + strDay;
                        std::string strMonth = boost::lexical_cast<std::string>(day._monthOfYear);
                        if (day._monthOfYear < 10)
                            strMonth = "0" + strMonth;
                        std::string strYr = boost::lexical_cast<std::string>(day._year);
                        std::string outStr = strYr + "-" + strMonth + "-" + strDay;
                        output << outStr;
                        return output;
                    }

                    inline bool operator==(const Day &other) {
                        return this->_jdn == other._jdn;
                    }

                    inline bool operator!=(const Day &other) {
                        return this->_jdn != other._jdn;
                    }

                    inline bool operator<(const Day &other) {
                        return this->_jdn < other._jdn ? true : false;
                    }

                    inline bool operator<=(const Day &other) {
                        return this->_jdn <= other._jdn ? true : false;
                    }

                    inline bool operator>(const Day &other) {
                        return this->_jdn > other._jdn ? true : false;
                    }

                    inline bool operator>=(const Day &other) {
                        return this->_jdn >= other._jdn ? true : false;
                    }

                    inline Day operator+(int numDays) {
                        int jdnAdj = _jdn + numDays;
                        Day d(jdnAdj);
                        return d;
                    }

                    inline Day operator-(int numDays) {
                        int jdnAdj = _jdn - numDays;
                        Day d(jdnAdj);
                        return d;
                    }

                    inline int operator-(const Day &other) {
                        int diff = _jdn - other._jdn;
                        return diff;
                    }

                    /**
                    * Postfix
                    */
                    inline Day operator++(int) {
                        Day currDay(_jdn);
                        _jdn++;
                        Day d(_jdn);
                        *this = d;
                        return currDay;
                    }

                    /**
                    * Prefix
                    */
                    inline Day operator++() {
                        _jdn++;
                        Day d(_jdn);
                        *this = d;
                        return *this;
                    }


                    /**
                    * Postfix
                    */
                    inline Day operator--(int) {
                        Day currDay(_jdn);
                        --_jdn;
                        Day d(_jdn);
                        *this = d;
                        return currDay;
                    }

                    /**
                    * Prefix
                    */
                    inline Day operator--() {
                        --_jdn;
                        Day d(_jdn);
                        *this = d;
                        return *this;
                    }

                    inline Day operator += (int days) {
                        _jdn += days;
                        Day d(_jdn);
                        *this = d;
                        return *this;
                    }

                    inline Day operator -= (int days) {
                        _jdn -= days;
                        Day d(_jdn);
                        *this = d;
                        return *this;
                    }
                };
            }
        }
    }
}
#endif
