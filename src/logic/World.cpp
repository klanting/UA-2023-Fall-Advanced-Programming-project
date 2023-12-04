//
// Created by tibov on 25/11/23.
//

#include "World.h"
#include "fstream"
#include "iostream"

namespace Logic {

    World::World(std::shared_ptr<AbstractFactory> factory) {
        //temp reading file
        std::fstream f("maps/map1.txt");

        double i = -1;
        double j = -1;
        while (!f.eof()){
            char c = f.get();
            if (c == 'w'){
                std::shared_ptr<Subject> s = factory->createWall(Vector2D{i, j});
                entities.push_back(s);
                not_passable.push_back(s);
            }

            if (c == 'G'){
                std::shared_ptr<Subject> s = factory->createGhost(Vector2D{i, j});
                entities.push_back(s);
            }

            if (c == 'P'){
                std::shared_ptr<Subject> s = factory->createPacman(Vector2D{i, j});
                entities.push_back(s);
                pacman = s;
            }

            if (c == 'c'){
                std::shared_ptr<Subject> s = factory->createCoin(Vector2D{i, j});
                entities.push_back(s);
            }

            i += 0.10;

            if (c == '\n'){
                j += 0.10;
                i = -1;
            }
        }

        for (auto& e: entities){
            std::shared_ptr<Move::ModeManager> mm = e->getMoveManager();
            mm->makeDirection(pacman->getPosition()-e->getPosition(), {Vector2D{0,1}, Vector2D{0,-1}, Vector2D{1,0}, Vector2D{-1,0}});
        }

    }

    std::vector<std::weak_ptr<Subject>> World::checkCollision(std::shared_ptr<Subject> s) {
        std::vector<std::weak_ptr<Subject>> hits;
        for (std::shared_ptr<Subject> other: entities){
            if (s == other){
                continue;
            }

            if (s->collide(other).first){
                hits.push_back(other);
            }

        }
        return hits;
    }

    void World::doTick() {
        std::vector<std::weak_ptr<Subject>> to_be_removed = {};

        for (auto& e: entities){
            e->move();


            bool hit_wall = false;
            while (true){
                std::vector<std::weak_ptr<Subject>> hits = checkCollision(e);
                if (hits.empty()){
                    break;
                }

                for (auto hit: hits){
                    if (std::find(not_passable.begin(), not_passable.end(),hit.lock()) != not_passable.end()){
                        e->handleImpassable(hit);
                        hit_wall = true;

                    }
                }
            }


            /*
            if (hit_wall){
                std::vector<Vector2D> option_directions = {Vector2D{0,1}, Vector2D{0,-1}, Vector2D{1,0}, Vector2D{-1,0}};
                auto it = std::find(option_directions.begin(), option_directions.end(), e->getMoveManager()->getDirection());
                if (it != option_directions.end()){
                    option_directions.erase(it);
                }

                e->getMoveManager()->makeDirection(pacman->getPosition()-e->getPosition(), option_directions);
            }*/


            /*
            for (auto hit: hits){
                if (hit.lock()->isConsumable()){
                    //hit.lock()->handleDead(entities);

                    to_be_removed.push_back(hit);
                }
            }*/



        }

        for (auto e: to_be_removed){
            auto it = std::find(entities.begin(), entities.end(), e.lock());
            entities.erase(it);
        }

    }
} // Logic