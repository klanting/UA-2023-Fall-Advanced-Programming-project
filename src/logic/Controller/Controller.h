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
     * Design Pattern: SingleTon
     *
     * Here is a Controller, that decides the direction based on which input keys
     * This is a singleton to guarantee that everyone will use the same controller
     *
     * This controller will have a data_vector
     * This data_vector gives the direction we want to go to based on user input
     * On key press (Depending on key) we will add a vector to the data_vector
     * On Key Release we will remove one
     * */
    class Controller{
    public:
        /**
         * getInstance function for getting an instance of the Controller Singleton
         * */
        static std::shared_ptr<Controller> getInstance();

        /**
         * On User input MoveUp key
         * */
        void moveUp(bool pressed);

        /**
         * On User input MoveDown key
         * */
        void moveDown(bool pressed);

        /**
         * On User input MoveLeft key
         * */
        void moveLeft(bool pressed);

        /**
         * On User input MoveRight key
         * */
        void moveRight(bool pressed);

        /**
         * Clears all data with regards to pressed keys, this Object might still contain
         * (Used to prevent reading keys that were pressed at a time the were not affecting the things it is suppose to)
         * (example: we don't care about these Key presses in any other state than the Levelstate)
         * */
        void clear();

        /**
         * Getter for the resulting datavector determing the direction based on key presses
         * */
        [[nodiscard]] const Vector2D<>& getDataVector() const;
    private:

        /**
         * Private Constructor to support Singleton Design Pattern
         * */
        Controller();
        inline static std::shared_ptr<Controller> _instance;

        /**
         * check_press is a small helpfunction to calculate the new data_vector
         * */
        void check_press(bool pressed, int index, const Vector2D<>& change);
        bool pressed_table[4];
        Vector2D<> data_vector;

    };

} // Controller

#endif //PROJECTPACMAN_CONTROLLER_H
