//
// Created by tibov on 25/11/23.
//

#include "World.h"
#include "fstream"
#include "iostream"
namespace Logic {

    World::World(std::shared_ptr<AbstractFactory> concrete_factory) {
        //temp reading file
        std::fstream f("maps/map1.txt");

        double i = 0;
        double j = 0;
        while (!f.eof()){
            char c = f.get();
            if (c == 'w'){
                std::shared_ptr<Subject> s = concrete_factory->createWall(Vector2D{i, j});
                entities.push_back(s);
                not_passable.push_back(s);
            }
            i += 0.05;

            if (c == '\n'){
                j += 0.05;
                i = 0;
            }
        }
    }

    bool World::CheckCollision(std::shared_ptr<Subject> s) {
        for (std::shared_ptr<Subject> other: entities){
            if (s == other){
                continue;
            }

            Vector2D a = s->getPosition();
            Vector2D b = s->getSize() + a;


        }
        return false;
    }
} // Logic