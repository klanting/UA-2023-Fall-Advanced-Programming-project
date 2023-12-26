//
// Created by tibov on 25/11/23.
//

#ifndef PROJECTPACMAN_WORLD_H
#define PROJECTPACMAN_WORLD_H
#include "../Subjects/Subject.h"
#include "../Subjects/EntityModel.h"
#include "vector"
#include "../AbstractFactory.h"
#include "../Score.h"
#include <map>
#include <functional>

namespace Logic {

    class World {
    public:
        World(const std::shared_ptr<EntityModel>& pacman, const std::vector<std::shared_ptr<EntityModel>>& entities,
              const std::vector<std::shared_ptr<EntityModel>>& not_passable, const std::vector<std::shared_ptr<EntityModel>>& intersection, int lives, int consumable_count);
        bool doTick();

        int getLives() const;

    private:
        std::shared_ptr<EntityModel> pacman;
        std::vector<std::shared_ptr<EntityModel>> entities;
        std::vector<std::shared_ptr<EntityModel>> not_passable;
        std::vector<std::shared_ptr<EntityModel>> intersection;

        std::map<std::shared_ptr<EntityModel>, std::shared_ptr<EntityModel>> last_intersection;

        std::vector<std::weak_ptr<EntityModel>> checkCollision(std::shared_ptr<EntityModel> s, int type = 0);

        void handleInPassable(std::shared_ptr<EntityModel> e);
        void handleHit(std::shared_ptr<EntityModel> e);
        void handleIntersection(std::shared_ptr<EntityModel> e);

        void handleActionsPacman(std::shared_ptr<EntityModel> e, std::weak_ptr<EntityModel> hit);
        void handleActions(std::shared_ptr<EntityModel> e, std::weak_ptr<EntityModel> hit);

        std::vector<Vector2D<>> getFutureDirections(std::shared_ptr<EntityModel> e, const std::vector<Vector2D<>>& options);


        void dealCollision(const std::shared_ptr<EntityModel>& e, const std::weak_ptr<EntityModel>& hit, bool fix);
        void dealIntersection(const std::shared_ptr<EntityModel>& e, const std::weak_ptr<EntityModel>& hit);

        bool checkCollision(const std::shared_ptr<EntityModel>& s, const std::vector<std::shared_ptr<EntityModel>>& others, const std::function<void(std::shared_ptr<EntityModel>, std::weak_ptr<EntityModel>)>& op);
        void reCalculateDirection(const std::shared_ptr<EntityModel>& e);


        std::vector<std::weak_ptr<EntityModel>> to_be_removed;
        int lives;
        int consumable_count;
    };



} // Logic

#endif //PROJECTPACMAN_WORLD_H
