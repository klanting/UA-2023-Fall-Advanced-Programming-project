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

    }


} // Logic