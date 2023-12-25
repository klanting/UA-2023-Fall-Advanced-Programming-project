//
// Created by tibov on 25/11/23.
//

#ifndef PROJECTPACMAN_CONTROLMODE_H
#define PROJECTPACMAN_CONTROLMODE_H
#include "Mode.h"

#include "../Controller/Controller.h"
#include <algorithm>
#include "../Controller/Controller.h"

    namespace Logic::Move {

        /**
         * This Mode will depend his Direction on a Controller
         * The Controller is a Singleton so we can easley access it from within the ControlMode
         * */
        class ControlMode: public Mode{
        public:
            /**
             * Initialize the ControlMode Object
             * */
            ControlMode() =default;

            /**
             * Destructor for ControlMode
             * */
            ~ControlMode() override = default;

            /**
             * this function is not really needed for this Derived class
             * */
            void makeDirection(const Vector2D<>& to_pacman, const std::vector<Vector2D<>>& options) override;

            /**
             * Instead of getting the direction that is a data member of Mode we will take the direction of the Controller
             * */
            [[nodiscard]] const Vector2D<> &getDirection() const override;
        private:

        };

    } // Logic
// Move

#endif //PROJECTPACMAN_CONTROLMODE_H
