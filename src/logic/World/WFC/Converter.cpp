//
// Created by tibov on 25/12/23.
//

#include "Converter.h"
#include <fstream>
#include <iostream>
#include <algorithm>
namespace Logic {
    namespace WFC {
        Converter::Converter(const Matrix<int> &m): m{m} {
            std::vector<Vector2D<int>> directions = {Vector2D<int>{1, 0}, Vector2D<int>{0, 1}};
            for (int j = 0; j<Converter::m.getHeight(); j++){
                for (int i = 0; i<Converter::m.getWidth(); i++){
                    if (Converter::m.get(i, j) == 0){
                        bool broke = false;
                        for (auto dir: directions){
                            bool checked = check(Vector2D<int>{i, j}, dir);
                            if (checked){
                                broke = true;
                                break;
                            }
                        }

                        if (!broke){
                            Converter::m.set(i, j, -1);
                            addWall(Vector2D<int>{i, j}, Vector2D<int>{0, 0});
                        }


                    }else if (Converter::m.get(i, j) == -2){
                        ghost_spawn = std::make_unique<Vector2D<>>(Vector2D<>{i/10.0-1.0, j/10.0-1.0});
                    }else if (Converter::m.get(i, j) == 2){
                        addIntersection(Vector2D<int>{i, j});
                    }
                }
            }



        }

        bool Converter::check(const Vector2D<int> &start_pos, const Vector2D<int> &direction) {
            int distance = 0;

            int i;
            do{
                distance += 1;
                Vector2D new_pos = start_pos+ direction*distance;
                if (new_pos[0] > m.getWidth()-1 || new_pos[1] > m.getHeight()-1){
                    break;
                }
                i = m.get(new_pos[0], new_pos[1]);


            }while(i == 0);

            if (distance > 1){
                distance -= 1;
                for (int j = 0; j<=distance; j++){
                    Vector2D new_pos = start_pos+ direction*j;
                    m.set(new_pos[0], new_pos[1], -1);
                }
                Vector2D size = direction*distance;
                addWall(start_pos, size);

                return true;
            }

            return false;

        }

        void Converter::exportData() const {
            std::ofstream file("maps/mapGen.wrd");
            for (auto w: wall_positions){
                file << 0 << " " << w.first[0] << " " << w.first[1] << " " << w.second[0] << " " << w.second[1] << std::endl;
            }

            for (auto w:intersection_positions){
                file << 1 << " " << w.first[0] << " " << w.first[1] << " " << w.second[0] << " " << w.second[1] << std::endl;
            }

            file << 2 << " " << (*ghost_spawn)[0] << " " << (*ghost_spawn)[1]+0.05 << std::endl;
        }

        void Converter::addWall(const Vector2D<int> &start_pos, const Vector2D<int> &size) {

            Vector2D<> extra_offset{0, 0};
            Vector2D<> extra_size{0, 0};
            for (auto n: {Vector2D<int>{0, 1}, Vector2D<int>{1, 0}}){
                Vector2D temp = start_pos - n;

                if (temp[0] >= 0 && temp[1] >= 0 && m.get(temp[0], temp[1]) == -1){
                    extra_offset -= Vector2D<>{0.05*n[0], 0.05*n[1]};
                    extra_size += Vector2D<>{0.05*n[0], 0.05*n[1]};
                }

                temp = start_pos + size + n;
                if (temp[0] < m.getWidth() && temp[1] < m.getHeight() && m.get(temp[0], temp[1]) == -1){
                    extra_size += Vector2D<>{0.05*n[0], 0.05*n[1]};
                }
            }


            Vector2D<> new_start = Vector2D<>{(start_pos[0]/10.0)-1.0, (start_pos[1]/10.0)-1.0};
            new_start += offset;
            new_start += extra_offset;
            Vector2D new_size = Vector2D<>{(size[0]/10.0)+0.05, (size[1]/10.0)+0.05};
            new_size += extra_size;
            wall_positions.push_back(std::make_pair(new_start, new_size));

        }

        void Converter::addIntersection(const Vector2D<int> &start_pos) {
            Vector2D<> new_start = Vector2D<>{(start_pos[0]/10.0)-1.0, (start_pos[1]/10.0)-1.0};
            new_start += Vector2D<>{-0.025, 0.025};
            Vector2D new_size = Vector2D<>{0.15, 0.15};

            intersection_positions.push_back(std::make_pair(new_start, new_size));

        }
    } // WFC
} // Logic