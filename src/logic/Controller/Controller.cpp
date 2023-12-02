//
// Created by tibov on 25/11/23.
//

#include "Controller.h"
namespace Controller {

    const Vector2D &Controller::getDataVector() const {
        return data_vector;
    }

    Controller::Controller(): data_vector{Vector2D{0,0}} {


    }
} // Controller