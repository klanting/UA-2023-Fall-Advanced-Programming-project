//
// Created by tibov on 25/11/23.
//

#ifndef PROJECTPACMAN_CONTROLLER_H
#define PROJECTPACMAN_CONTROLLER_H
#include <memory>
#include <vector>
#include "../Vector2D.h"
namespace Controller {

    class ControllerObserver;

    using namespace Logic;
    class Controller {
    public:
        Controller();

        virtual void moveUp(bool pressed) = 0;
        virtual void moveDown(bool pressed) = 0;
        virtual void moveLeft(bool pressed) = 0;
        virtual void moveRight(bool pressed) = 0;

        void addObserver(std::shared_ptr<ControllerObserver> controller_observer);
        const Vector2D &getDataVector() const;

    protected:
        Vector2D data_vector;
        std::vector<std::shared_ptr<ControllerObserver>> observers;

    };

} // Controller

#endif //PROJECTPACMAN_CONTROLLER_H
