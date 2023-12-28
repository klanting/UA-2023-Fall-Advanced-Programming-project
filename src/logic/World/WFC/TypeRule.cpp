//
// Created by tibov on 25/12/23.
//

#include "TypeRule.h"


    namespace Logic::WFC {
        void TypeRule::add(int index, int neighbour_type) {
            int count = options.get(neighbour_type, index);
            options.set(neighbour_type, index, count+1);

        }

        TypeRule::TypeRule(int size, int direction_size): options{size, direction_size, 0} {


        }

        std::set<int> TypeRule::getOptions(int index) const {
            std::set<int> output;
            for (int i = 0; i<options.getWidth(); i++){
                int v = options.get(i, index);
                if (v != 0){
                    output.insert(i);
                }
            }
            return output;
        }
    } // WFC
// Logic