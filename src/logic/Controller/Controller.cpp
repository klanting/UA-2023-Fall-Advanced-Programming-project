#include "Controller.h"

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

        }

        //On key Release
        if (!pressed && pressed_key){
            pressed_table[index] = false;
            data_vector -= change;
        }

    }

    Controller::Controller(): data_vector{0, 0}, pressed_table{false, false, false, false} {

    }

    std::shared_ptr<Controller> Controller::getInstance() {
        if (!_instance){
            _instance = std::shared_ptr<Controller>(new Controller());
        }
        return _instance;
    }


    void Controller::clear() {
        //Reset all keys that are pressed
        for (bool &i : pressed_table){
            i = false;
        }
        data_vector = Vector2D<>{0, 0};

    }

    const Vector2D<>& Controller::getDataVector() const{
        return data_vector;
    }
} // Controller