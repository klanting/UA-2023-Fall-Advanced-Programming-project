//
// Created by tibov on 25/11/23.
//

#include "ChaseMode.h"

namespace Logic {
    namespace Move {
        void ChaseMode::makeDirection(const Vector2D &to_pacman, const std::vector<Vector2D> &options){
            std::shared_ptr<Random> r = Random::getInstance();
            double choice_value = r->getRandom();


            if (choice_value < 0.5){
                //this choice will choose a random option
                direction = takeRandom(options);
            }else{
                //this choice is chose closest option
                direction = findBest(to_pacman, options, std::less());
            }


        }




    } // Move
} //Logic