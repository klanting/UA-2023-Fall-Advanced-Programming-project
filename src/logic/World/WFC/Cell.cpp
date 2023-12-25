//
// Created by tibov on 25/12/23.
//

#include "Cell.h"

namespace Logic {
    namespace WFC {
        Cell::Cell(int size) {
            entropy = size;
            for (int i=0; i<size; i++){
                options.insert(i);
            }
        }

        void Cell::place(int type) {
            if (defined){
                return;
            }

            defined = true;
            entropy = 0;

            key = type;

        }

        void Cell::updateValue(const std::set<int> &acceptable) {
            if (defined){
                return;
            }
            std::set<int> resulting;

            std::set_intersection(acceptable.begin(), acceptable.end(), options.begin(), options.end(), std::inserter(resulting, resulting.begin()));
            options = resulting;

            entropy = options.size();

        }

        double Cell::getEntropy() const {
            return entropy;
        }

        int Cell::getKey() const {
            return key;
        }

        bool Cell::isDefined() const {
            return defined;
        }

        const std::set<int> &Cell::getOptions() const {
            return options;
        }
    } // WFC
} // Logic