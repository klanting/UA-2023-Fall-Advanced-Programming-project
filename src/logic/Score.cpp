//
// Created by tibov on 03/12/23.
//

#include "Score.h"
#include <iostream>
#include <cmath>
namespace Logic {
    Score::Score(): score{0}, time_till_last{0} {

    }

    void Score::moved() {
        time_till_last += Stopwatch::getInstance()->getDeltaTime();
    }

    void Score::consume(std::weak_ptr<EntityModel> other) {
        auto o = other.lock();

        score += std::max(5.0*(2-time_till_last), 1.0);
        score += o->bonus();
        time_till_last = 0;
        std::cout << "score " << score << std::endl;
    }

    void Score::died() {

    }

    int Score::getScore() const{
        return std::floor(score);
    }

    void Score::addObserved(const std::weak_ptr<EntityModel>& pacman_ptr) {
        Score::pacman = pacman_ptr;

    }

    void Score::finishedLvl() {
        score += 100;
    }
} // Logic