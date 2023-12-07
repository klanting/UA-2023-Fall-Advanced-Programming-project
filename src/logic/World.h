//
// Created by tibov on 25/11/23.
//

#ifndef PROJECTPACMAN_WORLD_H
#define PROJECTPACMAN_WORLD_H
#include "Subjects/Subject.h"
#include "Subjects/EntityModel.h"
#include "vector"
#include "AbstractFactory.h"
namespace Logic {

    class World {
    public:
        World(std::shared_ptr<AbstractFactory> factory);
        bool doTick();
    private:
        std::vector<std::shared_ptr<EntityModel>> entities;
        std::vector<std::shared_ptr<EntityModel>> not_passable;
        std::shared_ptr<EntityModel> pacman;

        std::vector<std::weak_ptr<EntityModel>> checkCollision(std::shared_ptr<EntityModel> s, bool inpassable = false);
        void handleInPassable(std::shared_ptr<EntityModel> e);
        void handleActionsPacman(std::shared_ptr<EntityModel> e, std::weak_ptr<EntityModel> hit, std::vector<std::weak_ptr<EntityModel>>& to_be_removed);
        void handleActions(std::shared_ptr<EntityModel> e, std::weak_ptr<EntityModel> hit, std::vector<std::weak_ptr<EntityModel>>& to_be_removed);

        int lives;
    };



} // Logic

#endif //PROJECTPACMAN_WORLD_H
