//
// Created by tibov on 25/11/23.
//

#ifndef PROJECTPACMAN_FEARMODE_H
#define PROJECTPACMAN_FEARMODE_H
#include "Mode.h"

    namespace Logic::Move {

        /**
         * Chase Mode will decide its direction by the following steps
         * 50% chance it takes a random direction (within possible options)
         * 50% chance it want to maximize the Manhattan distance with a give Entity Direction in my project: Direction to Pacman
         * To maximize the Manhattan distance with a given entity it will use the angle between 2 vectors
         * The direction with the highest Manhattan distance will be the one with the biggest angle between the vector
         * Towards the other entity
         * */
        class FearMode: public Mode{
        public:
            /**
             * Initialize the FearMode Object
             * */
            FearMode() = default;

            /**
             * Destructor for FearMode
             * */
            ~FearMode() override = default;

            /**
             * makeDirection function
             * This function will decide the new direction based of the following rules
             * 50% chance it takes a random direction (within possible options)
             * 50% chance it want to maximize the Manhattan distance with a give Entity Direction in my project: Direction to Pacman
             * */
            void makeDirection(const Vector2D<>& to_entity, const std::vector<Vector2D<>>& options) override;
        private:

        };

    } // Logic
// Move

#endif //PROJECTPACMAN_FEARMODE_H
