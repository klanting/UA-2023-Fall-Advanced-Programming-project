//
// Created by tibov on 03/12/23.
//

#include "Score.h"
#include <iostream>
namespace Logic {
    Score::Score(std::weak_ptr<EntityModel> pacman): pacman{pacman}, score{0}, time_till_last{0} {

    }

    void Score::moved() {
        time_till_last += Stopwatch::getInstance()->getDeltaTime();
    }

    void Score::consume(std::weak_ptr<Subject> other) {
        auto o = other.lock();

        score += 1.0*(1/time_till_last);
        time_till_last = 0;
        std::cout << "score " << score << std::endl;
    }

    void Score::died() {

    }
} // Logic