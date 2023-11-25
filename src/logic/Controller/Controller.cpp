//
// Created by tibov on 25/11/23.
//

#include "Controller.h"
#include "ControllerObserver.h"
namespace Controller {
    void Controller::addObserver(std::shared_ptr<ControllerObserver> controller_observer) {
        observers.push_back(controller_observer);

    }

    const Vector2D &Controller::getDataVector() const {
        return data_vector;
    }
} // Controller