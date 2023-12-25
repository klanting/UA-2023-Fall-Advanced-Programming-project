//
// Created by tibov on 25/11/23.
//

#ifndef PROJECTPACMAN_CHASEMODE_H
#define PROJECTPACMAN_CHASEMODE_H
#include "Mode.h"

    namespace Logic::Move {

        /**
         * Part of Design Pattern: Strategy
         * Derived Class of Class Mode
         * Chase Mode will decide its direction by the following steps
         * 50% chance it takes a random direction (within possible options)
         * 50% chance it want to minimize the Manhattan distance with a give Entity Direction in my project: Direction to Pacman
         * To reduce the Manhattan distance with a given entity it will use the angle between 2 vectors
         * The direction with the lowest Manhattan distance will be the one with the lowest angle between the vector
         * Towards the other entity
         * */
        class ChaseMode: public Mode{
        public:
            /**
             * Initialize the ChaseMode Object
             * */
            ChaseMode() = default;

            /**
             * Destructor for ChaseMode
             * */
            ~ChaseMode() override = default;

            /**
             * makeDirection function
             * This function will decide the new direction based of the following rules
             * 50% chance it takes a random direction (within possible options)
             * 50% chance it want to minimize the Manhattan distance with a give Entity Direction in my project: Direction to Pacman
             * */
            void makeDirection(const Vector2D<>& to_entity, const std::vector<Vector2D<>>& options) override;

        private:

        };

    } // Logic
// Move

#endif //PROJECTPACMAN_CHASEMODE_H
