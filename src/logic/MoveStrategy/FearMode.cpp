//
// Created by tibov on 25/11/23.
//

#include "FearMode.h"
#include <iostream>

    namespace Logic::Move {
        void FearMode::makeDirection(const Vector2D<> &to_entity, const std::vector<Vector2D<>> &options){

            //decide between random choice or Manhattan choice
            std::shared_ptr<Random> r = Random::getInstance();
            double choice_value = r->getRandom();


            if (choice_value < 0.5){
                //this choice will choose a random option
                direction = takeRandom(options);
            }else{
                //this choice is will choose the Direction that brings the Entity closest to Entity
                direction = findBest(to_entity, options, std::greater());
            }
        }
    } // Logic
// Move