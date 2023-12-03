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
        for (auto& e: entities){
            e->move();

            std::vector<std::weak_ptr<Subject>> hits = checkCollision(e);
            if (hits.empty()){
                continue;
            }


            for (auto hit: hits){
                if (std::find(not_passable.begin(), not_passable.end(),hit.lock()) != not_passable.end()){
                    e->handleImpassable(hit);
                }
            }

            std::vector<Vector2D> option_directions = {Vector2D{0,1}, Vector2D{0,-1}, Vector2D{1,0}, Vector2D{-1,0}};
            auto it = std::find(option_directions.begin(), option_directions.end(), e->getMoveManager()->getDirection());
            if (it != option_directions.end()){
                option_directions.erase(it);
            }


            e->getMoveManager()->makeDirection(pacman->getPosition()-e->getPosition(), option_directions);


        }

    }
} // Logic