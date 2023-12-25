//
// Created by tibov on 25/12/23.
//

#include "TypeRuleManager.h"
#include <iostream>
namespace Logic {
    namespace WFC {
        TypeRuleManager::TypeRuleManager(const std::string &file_path, const std::vector<Vector2D<int>> &directions) {
            int file_width = 19;
            int file_height = 9;

            Matrix<int> buffer{file_width, file_height, 0};

            int x = 0;
            int y = 0;
            int id_counter = 6;
            std::map<char, int> count_table;
            count_table.insert({'0', 0});
            count_table.insert({'1', 1});
            count_table.insert({'2', 2});
            count_table.insert({'3', 3});
            count_table.insert({'4', 4});
            count_table.insert({'5', 5});

            std::ifstream file(file_path);
            while (!file.eof()){
                char c = file.get();
                if (c == '\n'){
                    y += 1;
                    x = 0;
                    continue;
                }

                if ((int) c == -1){
                    break;
                }

                int a;

                auto it = count_table.find(c);
                if (it == count_table.end()){
                    count_table.insert({c, id_counter});

                    a = id_counter;
                    id_counter++;

                }else{
                    a = it->second;
                }

                buffer.set(x, y, a);
                x += 1;
            }

            for (int i = 0; i<id_counter; i++){
                type_map.insert({i, TypeRule{id_counter, (int) directions.size()}});
            }

            for (int j = 0; j<file_height; j++){
                for (int i = 0; i<file_width; i++){
                    int own = buffer.get(i, j);
                    for (int dir = 0; dir<directions.size(); dir++){
                        auto p = directions[dir];
                        if (j+p[1] < 0 || j+p[1] >= file_height){
                            continue;
                        }
                        if (i+p[0] < 0 || i+p[0] >= file_width){
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


    } // WFC
} // Logic