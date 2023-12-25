//
// Created by tibov on 25/11/23.
//

#include "Controller.h"
#include <iostream>
namespace Controller {

    void Controller::moveUp(bool pressed) {
        check_press(pressed, 0, Vector2D<>{0, -1});

    }

    void Controller::moveDown(bool pressed) {
        check_press(pressed, 1, Vector2D<>{0, 1});
    }

    void Controller::moveLeft(bool pressed) {
        check_press(pressed, 2, Vector2D<>{-1, 0});
    }

    void Controller::moveRight(bool pressed) {
        check_press(pressed, 3, Vector2D<>{1, 0});
    }


    void Controller::check_press(bool pressed, int index, const Vector2D<>& change) {
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

    Controller::Controller(): data_vector{0, 0} {

    }

    std::shared_ptr<Controller> Controller::getInstance() {
        if (!_instance){
            _instance = std::shared_ptr<Controller>(new Controller());
        }
        return _instance;
    }

    void Controller::reset_all_moves() {
        //Reset all keys that are pressed
        for (int i=0; i<4; i++){
            pressed_table[i] = false;
        }
        data_vector = Vector2D<>{0, 0};
    }

    void Controller::clear() {
        //Interface from the outside to clear all moves
        reset_all_moves();

    }

    const Vector2D<>& Controller::getDataVector() const{
        return data_vector;
    }
} // Controller