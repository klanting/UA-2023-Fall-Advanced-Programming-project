//
// Created by tibov on 25/12/23.
//

#ifndef PROJECTPACMAN_CELL_H
#define PROJECTPACMAN_CELL_H

#include "vector"
#include "string"
#include <map>
#include <set>
#include <fstream>
#include <algorithm>
#include <iostream>

namespace Logic {
    namespace WFC {

        class Cell {
        public:
            Cell(int size);
            void place(int type);
            bool updateValue(const std::set<int>& acceptable);

            double getEntropy() const;

            int getKey() const;

            bool isDefined() const;

            const std::set<int> &getOptions() const;

            void remove(int i);

            bool operator==(const Cell& other);

        private:

            bool defined = false;
            std::set<int> options;
            double entropy = -1;
            int key = -1;



        };

    } // WFC
} // Logic

#endif //PROJECTPACMAN_CELL_H
