//
// Created by tibov on 25/11/23.
//

#ifndef PROJECTPACMAN_CONTROLLEROBSERVER_H
#define PROJECTPACMAN_CONTROLLEROBSERVER_H
#include "Controller.h"
#include <memory>
namespace Controller {

    class ControllerObserver {
    public:
        ControllerObserver();
        virtual void update(std::weak_ptr<Controller> input_controller) = 0;
    private:
    };

} // Controller

#endif //PROJECTPACMAN_CONTROLLEROBSERVER_H
