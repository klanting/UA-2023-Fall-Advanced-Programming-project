//
// Created by tibov on 25/11/23.
//

#ifndef PROJECTPACMAN_MOVEMENTCONTROLLER_H
#define PROJECTPACMAN_MOVEMENTCONTROLLER_H
#include "Controller.h"
namespace Controller {

    class MovementController: public Controller{
    public:
        MovementController() = default;

        void moveUp(bool pressed);
        void moveDown(bool pressed);
        void moveLeft(bool pressed);
        void moveRight(bool pressed);
    private:
        void check_press(bool pressed, int index, const Vector2D& change);
        bool pressed_table[4];
    };

} // Controller

#endif //PROJECTPACMAN_MOVEMENTCONTROLLER_H
