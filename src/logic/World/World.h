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
        /**
         * Constructor for World
         * This will get all its worldData when it is initialised by a WorldLoader
         * */
        World(const std::shared_ptr<EntityModel>& pacman, const std::vector<std::shared_ptr<EntityModel>>& entities,
              const std::vector<std::shared_ptr<EntityModel>>& not_passable, const std::vector<std::shared_ptr<EntityModel>>& intersection, int lives, int consumable_count);

        /**
         * This Function will simulate a tick
         * Doing the following steps:
         * Moving the Entities towards their given direction and handle their potential collision
         * with the other Entities
         * This will return a Boolean
         * if the bool is true we can continue playing this level
         * if false the game is over or Won
         * */
        bool doTick();

        /**
         * Getter for the remaining lives
         * */
        [[nodiscard]] int getLives() const;

        ~World();

    private:
        /**
         * ptr to the Pacman Entity
         * */
        std::shared_ptr<EntityModel> pacman;

        /**
         * Vector of All entities present except intersections
         * */
        std::vector<std::shared_ptr<EntityModel>> entities;

        /**
         * Vector of all entities that we can not pass through, in our project Walls
         * */
        std::vector<std::shared_ptr<EntityModel>> not_passable;

        /**
         * Vector of all intersections present in the map
         * */
        std::vector<std::shared_ptr<EntityModel>> intersection;

        /**
         * This map will store the last intersection visited by an entity
         * So we can guarantee to do the collision action when we reach the end of an intersection
         * */
        std::map<std::shared_ptr<EntityModel>, std::shared_ptr<EntityModel>> last_intersection;

        /**
         * this function will check if our entity e hits other entities and will handle this situation
         * */
        void handleHit(const std::shared_ptr<EntityModel>& e);

        /**
         * Pacman Will do the following rules when it hits the given entity
         * */
        void handleActionsPacman(const std::shared_ptr<EntityModel>& e, const std::weak_ptr<EntityModel>& hit);

        /**
         * other entities Will do the following rules when it hits the given entity
         * */
        void handleActions(const std::shared_ptr<EntityModel>& e, const std::weak_ptr<EntityModel>& hit);

        /**
         * This function will return all the direction our given entity can go to
         * This will check if we would go into a direction that we will not directly collide
         * */
        [[nodiscard]] std::vector<Vector2D<>> getFutureDirections(const std::shared_ptr<EntityModel>& e, const std::vector<Vector2D<>>& options) const;

        /**
         * This function will occur when an entity comes across an Intersection
         * */
        void dealIntersection(const std::shared_ptr<EntityModel>& e, const std::weak_ptr<EntityModel>& hit);

        /**
         * This function will check for Collision
         * s is the entity we want to check
         * others are all the entities we want to check with
         * op is a function ptr to the function we call on Collision
         * */
        static bool checkCollision(const std::shared_ptr<EntityModel>& s, const std::vector<std::shared_ptr<EntityModel>>& others, const std::function<void(std::shared_ptr<EntityModel>, std::weak_ptr<EntityModel>)>& op);

        /**
         * Function to change the direction of entity e
         * after a collision
         * */
        void reCalculateDirection(const std::shared_ptr<EntityModel>& e);

        /**
         * List of entities that need to be removed at the end of the tick
         * */
        std::vector<std::weak_ptr<EntityModel>> to_be_removed;

        /**
         * Remaining Lives
         * */
        int lives;

        /**
         * Amount of consumables left in the map
         * Used to determine if a game has been won
         * */
        int consumable_count;
    };



} // Logic

#endif //PROJECTPACMAN_WORLD_H
