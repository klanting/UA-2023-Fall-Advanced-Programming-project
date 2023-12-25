//
// Created by tibov on 25/12/23.
//

#ifndef PROJECTPACMAN_TYPERULE_H
#define PROJECTPACMAN_TYPERULE_H
#include <vector>
#include <set>

namespace Logic {
    namespace WFC {

        class TypeRule {
        public:
            TypeRule(int size, int direction_size);
            std::vector<std::vector<int>> options;

            void add(int index, int neighbour_type);
            std::set<int> getOptions(int index);
        private:

        };

    } // WFC
} // Logic

#endif //PROJECTPACMAN_TYPERULE_H
