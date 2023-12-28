//
// Created by tibov on 25/12/23.
//

#ifndef PROJECTPACMAN_TYPERULE_H
#define PROJECTPACMAN_TYPERULE_H
#include <vector>
#include <set>
#include "Matrix.h"

    namespace Logic::WFC {
        /**
         * This class will give the rules of a type
         * This will say which Types are allowed to be next to each other and on what side
         *
         * */
        class TypeRule {
        public:
            /**
             * Constructor for TypeRule
             * */
            TypeRule(int size, int direction_size);

            /**
             * matrix storing the options for a type
             * every row is another direction
             * and every column is an type that might be neighbouring
             * */
            Matrix<int> options;

            void add(int index, int neighbour_type);

            /**
             * get options for this type given a direction index
             * */
            [[nodiscard]] std::set<int> getOptions(int index) const;
        private:

        };

    } // WFC
// Logic

#endif //PROJECTPACMAN_TYPERULE_H
