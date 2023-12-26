//
// Created by tibov on 25/11/23.
//

#include "PassiveMode.h"


    namespace Logic::Move {
        void PassiveMode::makeDirection(const Vector2D<> &to_pacman, const std::vector<Vector2D<>> &options){
            //whatever happens keeps storing the empty vector{}
            direction = Vector2D<>{0, 0};
        }
    } // Logic
// Move