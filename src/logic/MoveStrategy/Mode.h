//
// Created by tibov on 25/11/23.
//

#ifndef PROJECTPACMAN_MODE_H
#define PROJECTPACMAN_MODE_H
#include "../Vector2D.h"
#include <vector>
#include <functional>
#include "../Random.h"
#include <algorithm>


    namespace Logic::Move {

        /**
         * Part of Design Pattern: Strategy
         * Mode is the strategy itself
         * Mode is an Abstract Class For the movement strategy
         * this Mode decides which direction an entity goes to
         * It calculates the new direction if needed
         * Each Entity will have its own ModeManager which contains a Mode
         * The Mode changes the method new directions are calculated
         * Making new ways to move Entities can be very easy implemented by adding Derived classes of This Mode Class
         * This also enables to change the Mode for certain entities without needing to change any code in the entity itself
         */
        class Mode {
        public:
            /**
             * Constructor for Mode Object
             * This initializes the direction to a default not moving direction
             */
            Mode();

            /**
             * Destructor for the Mode
             */
            virtual ~Mode() = default;

            /**
             * makeDirection will calculate the new direction we want to go to
             * As input parameters it can have 2 parameters:
             * to_entity is a vector towards another entity, it can be used to make te movement direction depend on the
             * relative location of another entity
             * options are all the optional direction we can go to
             */

            virtual void makeDirection(const Vector2D<>& to_entity, const std::vector<Vector2D<>>& options) = 0;

            /**
             * getter for the direction
             */
            [[nodiscard]] virtual const Vector2D<> &getDirection() const;


        protected:
            /**
             * Protected function that can be reused by multiple derived classes
             * This will find the closest/Furthest direction with regards to the to_entity
             * Whether it will minimize/maximize the distance will depend on the function parameter op
             * In our case we will use '<=' and '>' operators for Fear and Chase mode, but this can also be changed into
             * more complex functions
             */
            Vector2D<> findBest(const Vector2D<>& to_entity, const std::vector<Vector2D<>>& options, const std::function<bool(double, double)>& op) const;

            /**
             * Take a random direction among the directions that are possible
             */
            [[nodiscard]] Vector2D<> takeRandom(const std::vector<Vector2D<>>& options) const;

            /**
             * Stores current direction this Mode will go to till changed
             */
            Vector2D<> direction;
        private:

        };

    } // Logic
// Move

#endif //PROJECTPACMAN_MODE_H
