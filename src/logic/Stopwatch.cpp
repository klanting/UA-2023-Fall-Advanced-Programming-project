//
// Created by tibov on 25/11/23.
//

#include "Stopwatch.h"

namespace Logic {
    std::shared_ptr<Stopwatch> Stopwatch::getInstance() {
        if (!_instance){
            _instance = std::shared_ptr<Stopwatch>(new Stopwatch());
        }
        return _instance;
    }

    Stopwatch::Stopwatch() {
        //init stopwatch
        tick_iteration = 0;
        start_time = steady_clock::now();
        end_time = start_time;

    }

    double Stopwatch::getDeltaTime() const{
        return std::chrono::duration<double>(end_time-start_time).count();
    }

    void Stopwatch::doTick() {
        //set new end time, and set old end time as new start time
        start_time = end_time;
        end_time = steady_clock::now();
        tick_iteration += 1;

    }

    int Stopwatch::getTickIteration() const {
        return tick_iteration;
    }


} // Logic