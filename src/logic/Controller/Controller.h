//
// Created by tibov on 25/11/23.
//

#ifndef PROJECTPACMAN_CONTROLLER_H
#define PROJECTPACMAN_CONTROLLER_H
#include "../Vector2D.h"
#include <memory>
namespace Controller {
    using namespace Logic;

    /**
     * Here is a Controller, that decides the direction based on which input keys
     * This is a singleton to guarantee that everyone will use the same controller
     * */
    class Controller{
    public:
        static std::shared_ptr<Controller> getInstance();


        void moveUp(bool pressed);
        void moveDown(bool pressed);
        void moveLeft(bool pressed);
        void moveRight(bool pressed);
        void clear();
        const Vector2D<>& getDataVector() const;
    private:
        Controller();
        inline static std::shared_ptr<Controller> _instance;


        void check_press(bool pressed, int index, const Vector2D<>& change);
        bool pressed_table[4];
        Vector2D<> data_vector;

        void reset_all_moves();
    };

} // Controller

#endif //PROJECTPACMAN_CONTROLLER_H
