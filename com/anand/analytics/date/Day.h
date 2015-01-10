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
                    int dayOfMonth;
                    int monthOfYear;
                    int year;

                    bool isLeap;
                    int jdn;
                    DayofWeek dayofWeek;

                public:
                    int getDayOfMonth() const {
                        return dayOfMonth;
                    }

                    int getMonthOfYear() const {
                        return monthOfYear;
                    }

                    int getYear() const {
                        return year;
                    }

                    bool isIsLeap() const {
                        return isLeap;
                    }

                    DayofWeek getDayOfWeek() {
                        return dayofWeek;
                    }

                private:
                    int compute(int inputD, int inputM, int inputY ) {
                        int a = (14 - inputM) / 12;
                        int y = inputY + 4800 - a;
                        int m = inputM + 12 * a - 3;

                        int value = inputD + (153 * m + 2) / 5 + 365 * y + y / 4 - y / 100 + y / 400 - 32045;
                        //this->jdn = value;
                        return value;
                    }

                    DayofWeek computeDayOfWeek(int jdn) {
                        return static_cast<DayofWeek>((jdn + 1) % 7);
                    }

                public:
                    Day() {

                        boost::gregorian::date d(
                                boost::gregorian::day_clock::local_day()
                        );

                        dayOfMonth = d.day();
                        monthOfYear = d.month();
                        year = d.year();

                        jdn = compute(dayOfMonth, monthOfYear, year);
                        dayofWeek = computeDayOfWeek(jdn);
                    }

                    Day(int y, int m, int d) : dayOfMonth(d), monthOfYear(m), year(y) {
                        jdn = compute(dayOfMonth, monthOfYear, year);
                        dayofWeek = computeDayOfWeek(jdn);
                    }

                    Day(const Day &other) {
                        dayOfMonth = other.dayOfMonth;
                        monthOfYear = other.monthOfYear;
                        year = other.year;
                        jdn = other.jdn;
                        dayofWeek = other.dayofWeek;
                    }

                    Day(int julian) {
                        int i, j, k, l, n;

                        l = julian + 68569;
                        n = 4 * l / 146097;
                        l = l - (146097 * n + 3) / 4;
                        i = (4000 * (l + 1)) / 1461001;
                        l = l - (1461 * i) / 4 + 31;
                        j = (80 * l) / 2447;
                        k = l - (int) ((2447 * j) / 80);
                        l = j / 11;
                        j = j + 2 - (12 * l);
                        i = 100 * (n - 49) + i + l;

                        year = i;
                        monthOfYear = j;
                        dayOfMonth = k;

                        jdn = julian;
                        dayofWeek = computeDayOfWeek(jdn);
                    }

                    Day &operator=(const Day &other) {
                        dayOfMonth = other.dayOfMonth;
                        monthOfYear = other.monthOfYear;
                        year = other.year;

                        jdn = other.jdn;
                        dayofWeek = other.dayofWeek;
                        return *this;
                    }

                    friend ostream &operator<<(ostream &output,
                            const Day &day) {
                        std::string strDay = boost::lexical_cast<std::string>(day.dayOfMonth);
                        if (day.dayOfMonth < 10)
                            strDay = "0" + strDay;
                        std::string strMonth = boost::lexical_cast<std::string>(day.monthOfYear);
                        if (day.monthOfYear < 10)
                            strMonth = "0" + strMonth;
                        std::string strYr = boost::lexical_cast<std::string>(day.year);
                        std::string outStr = strYr + "-" + strMonth + "-" + strDay;
                        output << outStr;
                        return output;
                    }

                    inline bool operator==(const Day &other) {
                        return this->jdn == other.jdn;
                    }

                    inline bool operator!=(const Day &other) {
                        return this->jdn != other.jdn;
                    }

                    inline bool operator<(const Day &other) {
                        return this->jdn < other.jdn ? true : false;
                    }

                    inline bool operator<=(const Day &other) {
                        return this->jdn <= other.jdn ? true : false;
                    }

                    inline bool operator>(const Day &other) {
                        return this->jdn > other.jdn ? true : false;
                    }

                    inline bool operator>=(const Day &other) {
                        return this->jdn >= other.jdn ? true : false;
                    }

                    inline Day operator+(int numDays) {
                        int jdnAdj = jdn + numDays;
                        Day d(jdnAdj);
                        return d;
                    }

                    inline Day operator-(int numDays) {
                        int jdnAdj = jdn - numDays;
                        Day d(jdnAdj);
                        return d;
                    }

                    inline int operator-(const Day &other) {
                        int diff = jdn - other.jdn;
                        return diff;
                    }

                    /**
                    * Postfix
                    */
                    inline Day operator++(int) {
                        Day currDay(jdn);
                        jdn++;
                        Day d(jdn);
                        *this = d;
                        return currDay;
                    }

                    /**
                    * Prefix
                    */
                    inline Day operator++() {
                        jdn++;
                        Day d(jdn);
                        *this = d;
                        return *this;
                    }

                    inline Day operator += (int days) {
                        jdn += days;
                        Day d(jdn);
                        *this = d;
                        return *this;
                    }

                    inline Day operator -= (int days) {
                        jdn -= days;
                        Day d(jdn);
                        *this = d;
                        return *this;
                    }
                };
            }
        }
    }
}
#endif
