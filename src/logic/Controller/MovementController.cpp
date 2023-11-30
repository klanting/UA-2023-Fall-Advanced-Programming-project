//
// Created by tibov on 25/11/23.
//

#include "MovementController.h"
#include "ControllerObserver.h"
namespace Controller {

    void MovementController::moveUp(bool pressed) {
        check_press(pressed, 0, Vector2D{0, 1});

    }

    void MovementController::moveDown(bool pressed) {
        check_press(pressed, 0, Vector2D{0, -1});
    }

    void MovementController::moveLeft(bool pressed) {
        check_press(pressed, 0, Vector2D{-1, 0});
    }

    void MovementController::moveRight(bool pressed) {
        check_press(pressed, 0, Vector2D{1, 0});
    }


    void MovementController::check_press(bool pressed, int index, const Vector2D& change) {
        bool pressed_key = pressed_table[index];
        if (pressed && !pressed_key){
            pressed_table[index] = true;
            data_vector += change;
        }

        if (!pressed && pressed_key){
            pressed_table[index] = false;
            data_vector -= change;
        }

        for (std::shared_ptr<ControllerObserver> o: observers){
            o->update(std::shared_ptr<Controller>(this));
        }

    }

    MovementController::MovementController() {

    }
} // Controller