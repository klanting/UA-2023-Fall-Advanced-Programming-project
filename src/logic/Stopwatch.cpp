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
        start_time = steady_clock::now();
        end_time = start_time;



    }

    double Stopwatch::getDeltaTime() {
        return std::chrono::duration<double>(end_time-start_time).count();
    }

    void Stopwatch::doTick() {
        start_time = end_time;
        end_time = steady_clock::now();

    }


} // Logic