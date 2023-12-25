//
// Created by tibov on 25/11/23.
//

#include "MovementController.h"
#include <iostream>
namespace Controller {

    void MovementController::moveUp(bool pressed) {
        check_press(pressed, 0, Vector2D<>{0, -1});

    }

    void MovementController::moveDown(bool pressed) {
        check_press(pressed, 1, Vector2D<>{0, 1});
    }

    void MovementController::moveLeft(bool pressed) {
        check_press(pressed, 2, Vector2D<>{-1, 0});
    }

    void MovementController::moveRight(bool pressed) {
        check_press(pressed, 3, Vector2D<>{1, 0});
    }


    void MovementController::check_press(bool pressed, int index, const Vector2D<>& change) {
        //Check if key is already pressed
        bool pressed_key = pressed_table[index];

        //On key Press
        if (pressed && !pressed_key){
            pressed_table[index] = true;
            data_vector += change;
            std::cout << "P" << index << std::endl;


        }

        //On key Release
        if (!pressed && pressed_key){
            pressed_table[index] = false;
            data_vector -= change;
            std::cout << "R" << index << std::endl;
        }

    }

    MovementController::MovementController() {

    }

    std::shared_ptr<MovementController> MovementController::getInstance() {
        if (!_instance){
            _instance = std::shared_ptr<MovementController>(new MovementController());
        }
        return _instance;
    }

    void MovementController::reset_all_moves() {
        //Reset all keys that are pressed
        for (int i=0; i<4; i++){
            pressed_table[i] = false;
        }
        data_vector = Vector2D<>{0, 0};
    }

    void MovementController::clear() {
        //Interface from the outside to clear all moves
        reset_all_moves();

    }
} // Controller