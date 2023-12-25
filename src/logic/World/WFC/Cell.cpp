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

            options = {type};
            key = type;

        }

        bool Cell::updateValue(const std::set<int> &acceptable) {
            if (defined){
                return false;
            }
            std::set<int> resulting;

            std::set_intersection(acceptable.begin(), acceptable.end(), options.begin(), options.end(), std::inserter(resulting, resulting.begin()));
            options = resulting;

            if (options.size() == entropy){
                return false;
            }

            entropy = options.size();

            return true;

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

        void Cell::remove(int i) {
            options.erase(i);

        }
    } // WFC
} // Logic