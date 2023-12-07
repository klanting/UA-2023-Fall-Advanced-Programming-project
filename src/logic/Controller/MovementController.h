//
// Created by tibov on 25/11/23.
//

#ifndef PROJECTPACMAN_MOVEMENTCONTROLLER_H
#define PROJECTPACMAN_MOVEMENTCONTROLLER_H
#include "Controller.h"
namespace Controller {

    class MovementController: public Controller{
    public:
        static std::shared_ptr<MovementController> getInstance();



        void moveUp(bool pressed) override;
        void moveDown(bool pressed) override;
        void moveLeft(bool pressed) override;
        void moveRight(bool pressed) override;
        void clear() override;
    private:
        MovementController();
        inline static std::shared_ptr<MovementController> _instance;


        void check_press(bool pressed, int index, const Vector2D& change);
        bool pressed_table[4];

        void reset_all_moves();
    };

} // Controller

#endif //PROJECTPACMAN_MOVEMENTCONTROLLER_H
