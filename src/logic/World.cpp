//
// Created by tibov on 25/11/23.
//

#include "World.h"
#include "fstream"
#include "iostream"
namespace Logic {

    template <typename T>
    bool between(T a, T b, T c){
        //returns true if c is between a and b
        return a <= c && c <= b;
    }


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
                std::shared_ptr<Subject> s = factory->createGhost(Vector2D{i, j});
                entities.push_back(s);
            }

            i += 0.050;

            if (c == '\n'){
                j += 0.050;
                i = 0;
            }
        }

        std::weak_ptr<Subject> hit = checkCollision(entities[0]);
        if (hit.expired()){
            std::cout << "miss" << std::endl;
        }

    }

    std::weak_ptr<Subject> World::checkCollision(std::shared_ptr<Subject> s) {
        for (std::shared_ptr<Subject> other: entities){
            if (s == other){
                continue;
            }

            Vector2D a = s->getPosition();
            Vector2D b = s->getSize() + a;

            Vector2D c = other->getPosition();
            Vector2D d = other->getSize() + c;


            std::vector<Vector2D> baselines = {Vector2D{1, 0}, Vector2D{0, 1}};
            bool collided = true;
            for (auto& baseline: baselines){
                Vector2D a_c = a.projection(baseline);
                Vector2D b_c = b.projection(baseline);
                Vector2D c_c = c.projection(baseline);
                Vector2D d_c = d.projection(baseline);

                bool local_between = between<Logic::Vector2D>(a_c, b_c, c_c) || between<Logic::Vector2D>(c_c,d_c,a_c);
                if (!local_between){
                    collided = false;
                    break;
                }
            }

            if (collided){
                return std::weak_ptr<Subject>{other};
            }

        }
        return std::weak_ptr<Subject>{};
    }
} // Logic