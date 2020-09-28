//
// Created by Mateusz Raczynski on 8/16/2020.
//

#include "TemperatureScheduler.h"

void TemperatureScheduler::add(int iteration, GridValuesType<double>& array)
{
    if ((array.size() + 2) != sea->getCells().getRow() || (array[0].size() + 2) != sea->getCells().getCol()) {
        throw InconsistentSizeException();
    }
    bool present = (map.find(iteration) != map.end());
    if (present) {
        throw FilePresentedException();
    }
    map[iteration] = array;
}

void TemperatureScheduler::update(int iteration)
{
    auto it = map.find(iteration);
    if(it != map.end())
    {
        GridValuesType<double> &array = it->second;
        sea->setTemperature(array);
    }
}

TemperatureScheduler::TemperatureScheduler(std::shared_ptr<Sea> sea) : Scheduler(sea)
{

}

UpdateSubject TemperatureScheduler::getUpdateSubject(int iteration) {
    return UpdateSubject::TEMP;
}
