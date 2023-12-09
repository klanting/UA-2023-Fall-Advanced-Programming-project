//
// Created by tibov on 25/11/23.
//

#ifndef PROJECTPACMAN_WORLD_H
#define PROJECTPACMAN_WORLD_H
#include "Subjects/Subject.h"
#include "Subjects/EntityModel.h"
#include "vector"
#include "AbstractFactory.h"
#include "Score.h"
#include <map>
namespace Logic {

    class World {
    public:
        World(std::shared_ptr<AbstractFactory> factory, std::shared_ptr<Score> score);
        bool doTick();

        int getLives() const;

    private:
        std::vector<std::shared_ptr<EntityModel>> entities;
        std::vector<std::shared_ptr<EntityModel>> not_passable;
        std::shared_ptr<EntityModel> pacman;
        std::shared_ptr<EntityModel> debug_ghost;

        std::map<std::shared_ptr<EntityModel>, std::pair<Vector2D, Vector2D>> intersection_map;
        void linkIntersections(std::shared_ptr<EntityModel> entity);

        std::vector<std::weak_ptr<EntityModel>> checkCollision(std::shared_ptr<EntityModel> s, bool inpassable = false);
        void handleInPassable(std::shared_ptr<EntityModel> e);
        void handleActionsPacman(std::shared_ptr<EntityModel> e, std::weak_ptr<EntityModel> hit, std::vector<std::weak_ptr<EntityModel>>& to_be_removed);
        void handleActions(std::shared_ptr<EntityModel> e, std::weak_ptr<EntityModel> hit, std::vector<std::weak_ptr<EntityModel>>& to_be_removed);

        int lives;
    };



} // Logic

#endif //PROJECTPACMAN_WORLD_H
