//
// Created by tibov on 25/12/23.
//

#include "TypeRule.h"

namespace Logic {
    namespace WFC {
        void TypeRule::add(int index, int neighbour_type) {
            options[index][neighbour_type] += 1;

        }

        TypeRule::TypeRule(int size, int direction_size) {
            for (int i = 0; i<direction_size; i++){
                std::vector<int> mapping;
                for (int j = 0; j<size; j++){
                    mapping.push_back(0);
                }
                options.push_back(mapping);
            }

        }

        std::set<int> TypeRule::getOptions(int index) {
            std::set<int> output;
            for (int j = 0; j<options[index].size(); j++){
                int v = options[index][j];
                if (v != 0){
                    output.insert(j);
                }
            }
            return output;
        }
    } // WFC
} // Logic