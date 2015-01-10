#ifndef __DATERANGE_H
#define __DATERANGE_H

#include "Day.h"

namespace com {
    namespace anand {
        namespace analytics {
            namespace date {
                class DateRange {
                public:
                    virtual Day startDate() = 0;

                    virtual Day endDate() = 0;
                };
            }
        }
    }
}

#endif