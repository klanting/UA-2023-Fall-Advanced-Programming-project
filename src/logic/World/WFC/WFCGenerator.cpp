//
// Created by tibov on 25/12/23.
//

#include "WFCGenerator.h"
#include <fstream>
#include <iostream>
#include <algorithm>
namespace Logic {
    namespace WFC {
        WFCGenerator::WFCGenerator(std::unique_ptr<AbstractFactory> factory, const std::shared_ptr<Score>& score): m{0, 0, 0}, WorldLoader(std::move(factory), score) {




        }

        bool WFCGenerator::check(const Vector2D<int> &start_pos, const Vector2D<int> &direction) {
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



        void WFCGenerator::addWall(const Vector2D<int> &start_pos, const Vector2D<int> &size) {

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

            std::shared_ptr<EntityModel> w = factory->createWall(new_start, new_size);
            entities.push_back(w);
            not_passable.push_back(w);

        }

        void WFCGenerator::addIntersection(const Vector2D<int> &start_pos) {
            Vector2D<> new_start = Vector2D<>{(start_pos[0]/10.0)-1.0, (start_pos[1]/10.0)-1.0};
            new_start += Vector2D<>{-0.025, 0.025};
            Vector2D new_size = Vector2D<>{0.15, 0.15};

            std::shared_ptr<EntityModel> i = factory->createIntersection(new_start, new_size);
            intersection.push_back(i);

        }

        std::unique_ptr<World> WFCGenerator::load(double difficulty, int lives) {
            m = grid_gen.generateGridMap();
            readMatrix();

            int consumable_count = 0;

            std::shared_ptr<EntityModel> s = factory->createPacman(Vector2D<>{0, -0.0725}, score);
            entities.push_back(s);
            pacman = s;

            for (auto w: {Vector2D{-0.885, -0.835}, Vector2D{0.815, -0.035}}){
                s = factory->createFruit(w);
                entities.push_back(s);
                consumable_count += 1;
            }


            for (int i=0; i<4; i++){
                double delay = 1;

                if (i == 1){
                    delay = 2;
                }
                if (i>= 2){
                    delay = 5.0 * (i-1);
                }

                s = factory->createGhost(*ghost_spawn, delay, i, difficulty);
                s->getMoveManager()->makeDirection(pacman->getPosition()-s->getPosition(), {Vector2D<>{0, -1}});
                entities.push_back(s);
            }

            std::vector<std::shared_ptr<EntityModel>> coin_buffer;
            for (int i=-9; i<9; i++){
                for (int j=-9; j<0; j++){
                    s = factory->createCoin(Vector2D{i/10.0+0.025, j/10.0+0.0751});

                    if (i >= -2 && i <= 1 && j == -5){
                        continue;
                    }
                    if (i >= -1 && i <= 0 && j == -6){
                        continue;
                    }

                    bool found = false;
                    for (auto np: entities){
                        Vector2D np_pos = np->getPosition();
                        Vector2D np_pos2 = np->getPosition()+np->getSize();
                        if ((s->getPosition()+s->getSize())[0] >= np_pos[0] && (s->getPosition()+s->getSize())[0] <= np_pos2[0] && (s->getPosition()+s->getSize())[1] >= np_pos[1] && (s->getPosition()+s->getSize())[1] <= np_pos2[1]){
                            found = true;
                        }
                    }

                    if (!found){
                        coin_buffer.push_back(s);
                        consumable_count += 1;
                    }
                }
            }


            entities.insert(entities.begin(), coin_buffer.begin(), coin_buffer.end());


            std::unique_ptr<World> world_ptr = std::make_unique<World>(pacman, entities, not_passable, intersection, lives, consumable_count);

            entities.clear();
            not_passable.clear();
            intersection.clear();

            return world_ptr;
        }

        void WFCGenerator::readMatrix() {
            std::vector<Vector2D<int>> directions = {Vector2D<int>{1, 0}, Vector2D<int>{0, 1}};
            for (int j = 0; j < WFCGenerator::m.getHeight(); j++){
                for (int i = 0; i < WFCGenerator::m.getWidth(); i++){
                    if (WFCGenerator::m.get(i, j) == 0){
                        bool broke = false;
                        for (auto dir: directions){
                            bool checked = check(Vector2D<int>{i, j}, dir);
                            if (checked){
                                broke = true;
                                break;
                            }
                        }

                        if (!broke){
                            WFCGenerator::m.set(i, j, -1);
                            addWall(Vector2D<int>{i, j}, Vector2D<int>{0, 0});
                        }


                    }else if (WFCGenerator::m.get(i, j) == -2){
                        ghost_spawn = std::make_unique<Vector2D<>>(Vector2D<>{i/10.0-1.0, j/10.0-1.0});
                    }else if (WFCGenerator::m.get(i, j) == 2){
                        addIntersection(Vector2D<int>{i, j});
                    }
                }
            }

        }
    } // WFC
} // Logic