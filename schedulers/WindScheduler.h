//
// Created by Mateusz Raczynski on 8/16/2020.
//

#ifndef OILSPILL_WINDSCHEDULER_H
#define OILSPILL_WINDSCHEDULER_H


#include "Scheduler.h"

class WindScheduler: public Scheduler
{
public:
    WindScheduler(std::shared_ptr<Sea> sea);
    void add(int iteration, GridValuesType &array) override;
    void update(int iteration) override;
};


#endif //OILSPILL_WINDSCHEDULER_H
