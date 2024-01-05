//
// Created by tibov on 25/12/23.
//

#include "WFCGenerator.h"
#include <algorithm>

    namespace Logic::WFC {
        WFCGenerator::WFCGenerator(std::unique_ptr<AbstractFactory>&& factory, const std::shared_ptr<Score>& score): m{0, 0, 0}, WorldLoader(std::move(factory), score) {




        }

        bool WFCGenerator::check(const Vector2D<int> &start_pos, const Vector2D<int> &direction) {
            //to prevent short mini walls, we will go into the given direction
            //if the length is longer than 1 it will make a full wall of this

            //calculate the distance
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

            //check idstance and if longer than 1 make wall
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
            //stores a new wall from grid
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
            //stores intersection from grid
            Vector2D<> new_start = Vector2D<>{(start_pos[0]/10.0)-1.0, (start_pos[1]/10.0)-1.0};
            new_start += Vector2D<>{-0.025, 0.025};
            Vector2D new_size = Vector2D<>{0.15, 0.15};

            std::shared_ptr<EntityModel> i = factory->createIntersection(new_start, new_size);
            intersection.push_back(i);

        }

        std::unique_ptr<World> WFCGenerator::load(double difficulty, int lives) {
            //generates the world

            //generate grid map
            m = grid_gen.generateGridMap();

            //convert map to entities
            readMatrix();

            //add pacman
            Vector2D<> pacman_position = Vector2D<>{-0.01, -0.0725};
            std::shared_ptr<EntityModel> s = factory->createPacman(pacman_position, score);
            entities.push_back(s);
            pacman = s;

            //add fruits
            for (auto w: {Vector2D{-0.885, -0.835}, Vector2D{0.815, -0.035}}){
                s = factory->createFruit(w);
                entities.push_back(s);
                consumable_count += 1;
            }


            //add ghosts
            for (int i=0; i<4; i++){
                double delay = 0.5;

                if (i == 1){
                    delay = 0.6;
                }
                if (i>= 2){
                    delay = 5.0 * (i-1);
                }

                s = factory->createGhost(*ghost_spawn, delay, i, difficulty);
                s->getMoveManager()->makeDirection(pacman->getPosition()-s->getPosition(), {Vector2D<>{0, -1}});
                entities.push_back(s);
            }


            //create world
            std::unique_ptr<World> world_ptr = std::make_unique<World>(pacman, entities, not_passable, intersection, lives, consumable_count);

            //clear old data
            entities.clear();
            not_passable.clear();
            intersection.clear();
            consumable_count = 0;

            return world_ptr;
        }

        void WFCGenerator::readMatrix() {

            for (int j = 0; j < WFCGenerator::m.getHeight(); j++){
                for (int i = 0; i < WFCGenerator::m.getWidth(); i++){

                    switch (WFCGenerator::m.get(i, j)) {

                        case 0:
                            //case wall
                            createWall(i, j);
                            break;
                        case -2:
                            //case ghost spawn
                            ghost_spawn = std::make_unique<Vector2D<>>(Vector2D<>{i/10.0-1.0, j/10.0-1.0});
                            addIntersection(Vector2D<int>{i, j});
                            break;
                        case 2:
                            //case intersection
                            addIntersection(Vector2D<int>{i, j});
                        case 1:
                            if ((i == 1 && j == 1) || (i == m.getWidth()-2 && j == m.getHeight()-2) ){
                                break;
                            }
                            addCoin(Vector2D<int>{i, j});
                            break;

                    }
                }
            }

        }

        void WFCGenerator::createWall(int i, int j) {
            //create a wall, but check if we can merge it with another nearby wall
            std::vector<Vector2D<int>> directions = {Vector2D<int>{1, 0}, Vector2D<int>{0, 1}};
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

        }

        void WFCGenerator::addCoin(const Vector2D<int> &start_pos) {
            //add coin
            Vector2D<> new_start = Vector2D<>{(start_pos[0]/10.0)-1.0, (start_pos[1]/10.0)-1.0};
            new_start += Vector2D<>{0.025, 0.075};

            std::shared_ptr<EntityModel> i = factory->createCoin(new_start);
            entities.push_back(i);
            consumable_count += 1;

        }
    } // WFC
// Logic