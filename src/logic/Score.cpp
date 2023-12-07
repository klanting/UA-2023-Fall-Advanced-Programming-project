//
// Created by tibov on 03/12/23.
//

#include "Score.h"
#include <iostream>
#include "math.h"
namespace Logic {
    Score::Score(): score{0}, time_till_last{0} {

    }

    void Score::moved() {
        time_till_last += Stopwatch::getInstance()->getDeltaTime();
    }

    void Score::consume(std::weak_ptr<Subject> other) {
        auto o = other.lock();

        score += std::min(1.0*(1/time_till_last), 100.0);
        time_till_last = 0;
        std::cout << "score " << score << std::endl;
    }

    void Score::died() {

    }

    int Score::getScore() const{
        return std::floor(score);
    }

    void Score::addObserved(std::weak_ptr<EntityModel> pacman) {
        Score::pacman = pacman;

    }
} // Logic