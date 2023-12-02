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
    class Controller {
    public:
        Controller();

        virtual void moveUp(bool pressed) = 0;
        virtual void moveDown(bool pressed) = 0;
        virtual void moveLeft(bool pressed) = 0;
        virtual void moveRight(bool pressed) = 0;

        const Vector2D &getDataVector() const;

    protected:
        Vector2D data_vector;

    };

} // Controller

#endif //PROJECTPACMAN_CONTROLLER_H
