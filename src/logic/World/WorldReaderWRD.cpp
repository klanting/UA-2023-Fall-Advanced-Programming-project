//
// Created by tibov on 27/12/23.
//

#include <fstream>
#include "WorldReaderWRD.h"


    namespace Logic::WorldLoading {
        WorldReaderWRD::WorldReaderWRD(std::unique_ptr<AbstractFactory>&& factory, const std::shared_ptr<Score> &score): WorldReader(std::move(factory), score) {

        }

        std::unique_ptr<World> WorldReaderWRD::load(double difficulty, int lives) {
            std::shared_ptr<EntityModel> pacman;
            std::vector<std::shared_ptr<EntityModel>> entities;
            std::vector<std::shared_ptr<EntityModel>> not_passable;
            std::vector<std::shared_ptr<EntityModel>> intersection;
            int consumable_count = 0;

            //create pacman Entity
            std::shared_ptr<EntityModel> s = factory->createPacman(Vector2D<>{0, -0.0725}, score);
            entities.push_back(s);
            pacman = s;

            std::vector<std::pair<Vector2D<>, Vector2D<>>> wall_positions = {};
            std::vector<std::pair<Vector2D<>, Vector2D<>>> intersection_positions = {};
            Vector2D ghost_spawn = Vector2D{-0.07, -0.5};
            std::fstream f("maps/map_data.wrd");

            //read the file and store the wall_position and intersection position
            // also store ghost Spawn position if present
            std::string buffer;
            std::vector<double> doubles;
            while (!f.eof()){

                char c = (char) f.get();
                if (c == ' '){
                    doubles.push_back(std::stod(buffer));
                    buffer = "";
                }else if (c == '\n'){
                    doubles.push_back(std::stod(buffer));
                    if (doubles[0] == 0){
                        wall_positions.emplace_back(Vector2D{doubles[1], doubles[2]}, Vector2D{doubles[3], doubles[4]});
                    }else if (doubles[0] == 1){
                        intersection_positions.emplace_back(Vector2D{doubles[1], doubles[2]}, Vector2D{doubles[3], doubles[4]});
                    }else if (doubles[0] == 2){
                        ghost_spawn = Vector2D{doubles[1], doubles[2]};
                    }

                    doubles = {};
                    buffer = "";
                }else{
                    buffer += c;
                }
            }


            //create the wall Entities
            for (auto w: wall_positions){
                s = factory->createWall(w.first, w.second);
                entities.push_back(s);
                not_passable.push_back(s);
            }

            //create the Fruit Entities
            for (auto w: {Vector2D{-0.885, -0.835}, Vector2D{0.815, -0.035}}){
                s = factory->createFruit(w);
                entities.push_back(s);
                consumable_count += 1;
            }

            //cretae the Intersections
            for (auto w: intersection_positions){
                s = factory->createIntersection(w.first, w.second);
                intersection.push_back(s);
            }

            //Create the Ghosts
            for (int i=0; i<4; i++){
                double delay = 0.5;

                if (i == 1){
                    delay = 1;
                }
                if (i>= 2){
                    delay = 5.0 * (i-1);
                }

                s = factory->createGhost(ghost_spawn, delay, i, difficulty);
                s->getMoveManager()->makeDirection(pacman->getPosition()-s->getPosition(), {Vector2D<>{0, -1}});
                entities.push_back(s);
            }

            //Create Coins of all the places where it can be
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
                    for (const auto& np: entities){
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

            //create a world
            std::unique_ptr<World> world_ptr = std::make_unique<World>(pacman, entities, not_passable, intersection, lives, consumable_count);

            return world_ptr;
        }
    } // WorldLoading
// Logic