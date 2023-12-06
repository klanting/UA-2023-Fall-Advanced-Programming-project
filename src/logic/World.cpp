//
// Created by tibov on 25/11/23.
//

#include "World.h"
#include "fstream"
#include "iostream"

namespace Logic {

    World::World(std::shared_ptr<AbstractFactory> factory) {

        std::shared_ptr<Subject> s = factory->createPacman(Vector2D{0, -0.5});
        entities.push_back(s);
        pacman = s;

        std::vector<std::pair<Vector2D, Vector2D>> wall_positions = {};
        std::fstream f("maps/wall_positions2.txt");

        std::string buffer;
        std::vector<double> doubles;
        while (!f.eof()){

            char c = f.get();
            if (c == ' '){
                doubles.push_back(std::stod(buffer));
                buffer = "";
            }else if (c == '\n'){
                doubles.push_back(std::stod(buffer));
                wall_positions.push_back({Vector2D{doubles[0], doubles[1]}, Vector2D{doubles[2], doubles[3]}});
                doubles = {};
                buffer = "";
            }else{
                buffer += c;
            }
        }


        for (auto w: wall_positions){
            s = factory->createWall(w.first, w.second);
            entities.push_back(s);
            not_passable.push_back(s);
        }


    }

    std::vector<std::weak_ptr<Subject>> World::checkCollision(std::shared_ptr<Subject> s, bool inpassable) {
        std::vector<std::weak_ptr<Subject>> hits;

        Vector2D best_vector = Vector2D{2, 2};
        auto to_check = entities;
        if (inpassable){
            to_check = not_passable;
        }

        for (std::shared_ptr<Subject> other: to_check){
            if (s == other){
                continue;
            }

            auto p = s->collide(other);
            if (p.first){
                hits.push_back(other);
            }



        }
        return hits;
    }

    void World::doTick() {
        std::vector<std::weak_ptr<Subject>> to_be_removed = {};

        for (auto& e: entities){
            e->move();

            handleCollision(e);

            std::vector<std::weak_ptr<Subject>> hits = checkCollision(e);
            for (auto hit: hits){
                if (hit.lock()->isConsumable()){
                    if (hit.lock()->handleDead(entities)){
                        to_be_removed.push_back(hit);
                    }


                }
            }

            e->moveConfirm();

        }

        for (auto e: to_be_removed){
            auto it = std::find(entities.begin(), entities.end(), e.lock());
            entities.erase(it);
        }

    }

    void World::handleCollision(std::shared_ptr<Subject> e) {
        bool hit_wall = false;
        bool fix = true;
        bool collision = true;
        while (collision){
            std::vector<std::weak_ptr<Subject>> np;
            for (int i = 0; i<3;i++){
                std::vector<std::weak_ptr<Subject>> hits = checkCollision(e, true);
                if (hits.empty()){
                    collision = false;
                    break;
                }


                for (auto hit: hits){
                    e->handleImpassable(hit, fix &&  hits.size() < 3);
                    hit_wall = true;
                    np.push_back(hit);

                }
            }

            fix = false;

        }

        if (hit_wall){
            std::vector<Vector2D> option_directions = {Vector2D{0,1}, Vector2D{0,-1}, Vector2D{1,0}, Vector2D{-1,0}};
            auto it = std::find(option_directions.begin(), option_directions.end(), e->getMoveManager()->getDirection());
            if (it != option_directions.end()){
                option_directions.erase(it);
            }

            e->getMoveManager()->makeDirection(pacman->getPosition()-e->getPosition(), option_directions);
        }
    }
} // Logic