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

        double i = 0;
        double j = 0;
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

            i += 0.050;

            if (c == '\n'){
                j += 0.050;
                i = 0;
            }
        }

        /*
        std::weak_ptr<Subject> hit = checkCollision(entities[0]);
        if (hit.expired()){
            std::cout << "miss" << std::endl;
        }*/

        for (auto& e: entities){
            std::shared_ptr<Move::ModeManager> mm = e->getMoveManager();
            mm->makeDirection(pacman->getPosition()-e->getPosition(), {Vector2D{0,1}, Vector2D{0,-1}, Vector2D{1,0}, Vector2D{-1,0}});
        }

    }

    std::weak_ptr<Subject> World::checkCollision(std::shared_ptr<Subject> s) {
        for (std::shared_ptr<Subject> other: entities){
            if (s == other){
                continue;
            }

            if (s->collide(other)){
                return other;
            }

        }
        return std::weak_ptr<Subject>{};
    }

    void World::doTick() {
        for (auto& e: entities){
            if (e == pacman){
                int b = 0;
            }
            e->move();
        }

    }
} // Logic