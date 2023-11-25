//
// Created by tibov on 25/11/23.
//

#include "ChaseMode.h"

namespace Logic {
    namespace Move {
        Vector2D ChaseMode::getDirection(const Vector2D &to_pacman, const std::vector<Vector2D> &options) const {
            std::shared_ptr<Random> r = Random::getInstance();
            double choice_value = r->getRandom();


            if (choice_value < 0.5){
                //this choice will choose a random option
                return takeRandom(options);
            }else{
                //this choice is chose closest option
                return findBest(to_pacman, options, std::less());
            }


        }




    } // Move
} //Logic