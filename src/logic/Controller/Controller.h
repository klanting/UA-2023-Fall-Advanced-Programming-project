//
// Created by tibov on 25/11/23.
//

#ifndef PROJECTPACMAN_CONTROLLER_H
#define PROJECTPACMAN_CONTROLLER_H
#include <memory>
#include <vector>
#include "../Vector2D.h"
namespace Controller {
    using namespace Logic;

    /**
     * Here is the controller defined, this allows an easy interface to control
     * certain entities
     * This class is an Abstract class so it is possible to add other controllers with other behaviours
     * */
    class Controller {
    public:
        Controller();

        virtual void moveUp(bool pressed) = 0;
        virtual void moveDown(bool pressed) = 0;
        virtual void moveLeft(bool pressed) = 0;
        virtual void moveRight(bool pressed) = 0;
        virtual void clear() = 0;
        const Vector2D &getDataVector() const;

    protected:
        Vector2D data_vector;

    };

} // Controller

#endif //PROJECTPACMAN_CONTROLLER_H
