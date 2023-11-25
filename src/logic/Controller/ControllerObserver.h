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
        virtual void update(std::shared_ptr<Controller> input_controller);
    private:
    };

} // Controller

#endif //PROJECTPACMAN_CONTROLLEROBSERVER_H
