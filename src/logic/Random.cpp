//
// Created by tibov on 25/11/23.
//

#include "Random.h"

namespace Logic {

    std::shared_ptr<Random> Random::getInstance() {
        if (!_instance){
            _instance = std::shared_ptr<Random>(new Random());
        }
        return _instance;
    }

    double Random::getRandom() {
        std::uniform_real_distribution<> dis(0.0, 1.0);

        return dis(*generator);
    }

    int Random::getRandomIndex(int a, int b) {
        std::uniform_int_distribution<> dis(a, b);
        return dis(*generator);
    }

    Random::Random() {
        std::random_device rd;
        generator = std::make_unique<std::mt19937>(rd());
    }


} // Logic