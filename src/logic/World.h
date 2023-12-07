//
// Created by tibov on 25/11/23.
//

#ifndef PROJECTPACMAN_WORLD_H
#define PROJECTPACMAN_WORLD_H
#include "Subjects/Subject.h"
#include "vector"
#include "AbstractFactory.h"
namespace Logic {

    class World {
    public:
        World(std::shared_ptr<AbstractFactory> factory);
        bool doTick();
    private:
        std::vector<std::shared_ptr<Subject>> entities;
        std::vector<std::shared_ptr<Subject>> not_passable;
        std::shared_ptr<Subject> pacman;

        std::vector<std::weak_ptr<Subject>> checkCollision(std::shared_ptr<Subject> s, bool inpassable = false);
        void handleCollision(std::shared_ptr<Subject> e);

        int lives;
    };



} // Logic

#endif //PROJECTPACMAN_WORLD_H
