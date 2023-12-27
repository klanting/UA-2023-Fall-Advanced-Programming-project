//
// Created by tibov on 25/12/23.
//

#include "TypeRuleManager.h"
#include <iostream>

    namespace Logic::WFC {
        TypeRuleManager::TypeRuleManager(const std::string &file_path, const std::vector<Vector2D<int>> &directions) {
            WFCReader r{file_path};
            wall_count = r.getWallCount();
            int id_counter = r.getIdCounter();
            for (int i = 0; i<id_counter; i++){
                type_map.insert({i, TypeRule{id_counter+1, (int) directions.size()}});
            }
            //border of the screen
            type_map.insert({id_counter, TypeRule{id_counter+1, (int) directions.size()}});

            auto buffer = r.getGrid();

            for (int j = 0; j<r.getDataHeight(); j++){
                for (int i = 0; i<r.getDataWidth(); i++){
                    int own = buffer.get(i, j);
                    for (int dir = 0; dir<directions.size(); dir++){
                        auto p = directions[dir];
                        if (j+p[1] < 0 || j+p[1] >= r.getDataHeight()){
                            type_map.at(own).add(dir, id_counter);
                            int reverse_index = (dir/4)*4 +(dir + 2) % 4;
                            type_map.at(id_counter).add(reverse_index, own);
                            continue;
                        }
                        if (i+p[0] < 0 || i+p[0] >= r.getDataWidth()){
                            type_map.at(own).add(dir, id_counter);
                            int reverse_index = (dir/4)*4 +(dir + 2) % 4;
                            type_map.at(id_counter).add(reverse_index, own);
                            continue;
                        }

                        int n = buffer.get(i+p[0], j+p[1]);

                        type_map.at(own).add(dir, n);

                    }
                }
            }

        }

        std::set<int> TypeRuleManager::getOptions(int type, int direction_index) {
            return type_map.at(type).getOptions(direction_index);
        }


        int TypeRuleManager::getCharAmount() {
            return (int) type_map.size();
        }

        int TypeRuleManager::getWallCount() const {
            return wall_count;
        }


    } // WFC
// Logic