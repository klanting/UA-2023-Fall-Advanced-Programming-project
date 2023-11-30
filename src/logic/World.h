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
        World(std::shared_ptr<AbstractFactory> concrete_factory);

    private:
        std::vector<std::shared_ptr<Subject>> entities;
        std::vector<std::shared_ptr<Subject>> not_passable;

        bool CheckCollision(std::shared_ptr<Subject> s);
    };



} // Logic

#endif //PROJECTPACMAN_WORLD_H
