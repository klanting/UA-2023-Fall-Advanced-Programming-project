
#include "World.h"
#include <iostream>

namespace Logic {
    //Alias so we do not need to rewrite this long Alias
    using OnColFunc = std::function<void(std::shared_ptr<EntityModel>, std::weak_ptr<EntityModel>)>;

    World::World(const std::shared_ptr<EntityModel>& pacman, const std::vector<std::shared_ptr<EntityModel>>& entities,
    const std::vector<std::shared_ptr<EntityModel>>& not_passable, const std::vector<std::shared_ptr<EntityModel>>& intersection,
    int lives, int consumable_count) {
        //constructor initializes all the variables
        //this parameters will be crated in a WorldLoader
        World::lives = lives;
        World::pacman = pacman;
        World::entities = entities;
        World::not_passable = not_passable;
        World::intersection = intersection;
        World::consumable_count = consumable_count;

    }


    bool World::doTick() {
        to_be_removed.clear();

        for (auto& e: entities){
            //move the entity
            e->move();

            //check for collision if we go into 2 directions at the same time, we will still go to the direction not obstructed
            OnColFunc col_fix = [](const std::shared_ptr<EntityModel>& e, const std::weak_ptr<EntityModel>& other){e->handleInpassable(other,true);};
            bool hit = checkCollision(e, not_passable, col_fix);

            //check for collision if we collide something we will go back to the last position before the collision
            OnColFunc col_no_fix = [](const std::shared_ptr<EntityModel>& e, const std::weak_ptr<EntityModel>& other){e->handleInpassable(other,false);};
            bool hit2 = checkCollision(e, not_passable, col_no_fix);

            //on collision, we might want to change the direction we want to go to
            if (hit || hit2){
                reCalculateDirection(e);
            }

            handleHit(e);
            OnColFunc deal_intersect = [this](const std::shared_ptr<EntityModel>& e, const std::weak_ptr<EntityModel>& other){dealIntersection(e, other);};
            checkCollision(e, intersection, deal_intersect);

        }

        //remove all the entities that do not have to exist anymore
        for (const auto& e: to_be_removed){
            if (e.expired()){
                continue;
            }

            auto it = std::find(entities.begin(), entities.end(), e.lock());
            entities.erase(it);
            consumable_count -=1;
        }

        //move the intersection if it would ever be able to move
        for (const auto& i: intersection){
            i->move();
        }


        //check conditions for GameOver or Next Level
        bool alive = lives > 0;
        bool still_food = consumable_count > 0;

        return alive && still_food;

    }

    void World::handleActionsPacman(const std::shared_ptr<EntityModel>& e, const std::weak_ptr<EntityModel>& hit) {
        if (hit.expired()){
            throw std::bad_weak_ptr();
        }

        if (hit.lock()->isConsumable()){
            e->consume(hit);
            if (hit.lock()->handleDead(entities)){
                to_be_removed.push_back(hit);
            }

        } else{
            e->handleDead(entities);
            lives -= 1;
        }

    }

    void World::handleActions(const std::shared_ptr<EntityModel>& e, const std::weak_ptr<EntityModel>& hit) {
        if (hit.expired()){
            throw std::bad_weak_ptr();
        }

        //make sure only ghosts do this
        if (hit.lock() == pacman){
            handleActionsPacman(hit.lock(), e);
        }

    }

    int World::getLives() const {
        return lives;
    }

    void World::handleHit(const std::shared_ptr<EntityModel>& e) {

        OnColFunc func;

        if (e == pacman){

            func = [this](const std::shared_ptr<EntityModel>& e, const std::weak_ptr<EntityModel>& other){handleActionsPacman(e, other);};
        }else{
            func = [this](const std::shared_ptr<EntityModel>& e, const std::weak_ptr<EntityModel>& other){handleActions(e, other);};
        }

        checkCollision(e, entities, func);

    }

    std::vector<Vector2D<>>
    World::getFutureDirections(const std::shared_ptr<EntityModel>& e, const std::vector<Vector2D<>> &options) const{
        std::vector<Vector2D<>> option_resulting = {};
        for (auto o: options){


            Vector2D resultPos = e->getPosition()+o*0.05;
            bool walkable = true;
            for (const auto& np: not_passable){
                if (e->collideFuture(np, resultPos)){
                    walkable = false;
                }
            }
            if (walkable){
                option_resulting.push_back(o);
            }
        }

        return option_resulting;
    }

    void World::dealIntersection(const std::shared_ptr<EntityModel> &e, const std::weak_ptr<EntityModel> &hit) {
        if (hit.expired()){
            throw std::bad_weak_ptr();
        }
        auto it = last_intersection.find(e);
        if (it != last_intersection.end()){
            if (it->second == hit.lock()){
                //only care if we are inside the intersection
                Vector2D center = e->getPosition()+e->getSize()*0.5;
                Vector2D inter_cent = hit.lock()->getPosition()+hit.lock()->getSize()*0.5;
                if (center.getDistance(inter_cent) > (hit.lock()->getSize()*0.5)[0]){
                    return;
                }
                e->handleInpassable(hit, false);
                Vector2D old_dir = e->getDirection();
                std::vector<Vector2D<>> option_directions = {old_dir.rotate(M_PI/2.0), old_dir.rotate(-1*M_PI/2.0), old_dir};
                std::vector<Vector2D<>> resulting = getFutureDirections(e, option_directions);
                e->getMoveManager()->makeDirection(pacman->getPosition()-e->getPosition(), resulting);
                last_intersection.erase(it);
                return;

            }
        }
        if (it != last_intersection.end()){
            it->second = hit.lock();
        }else{
            last_intersection.insert({e, hit.lock()});
        }

    }

    bool World::checkCollision(const std::shared_ptr<EntityModel> &s,
                               const std::vector<std::shared_ptr<EntityModel>> &others,
                               const std::function<void(std::shared_ptr<EntityModel>,
                                                        std::weak_ptr<EntityModel>)> &op) {
        bool hit_something = false;

        for (const std::shared_ptr<EntityModel>& other: others){
            if (s == other){
                continue;
            }

            auto p = s->collide(other);
            if (p.first){
                op(s, other);
                hit_something = true;
            }

        }

        return hit_something;
    }

    void World::reCalculateDirection(const std::shared_ptr<EntityModel> &e) {
        std::vector<Vector2D<>> option_directions = {Vector2D<>{0,1}, Vector2D<>{0,-1}, Vector2D<>{1,0}, Vector2D<>{-1,0}};
        auto it = std::find(option_directions.begin(), option_directions.end(), e->getMoveManager()->getDirection());
        if (it != option_directions.end()){
            option_directions.erase(it);
        }
        auto it2 = std::find(option_directions.begin(), option_directions.end(), e->getMoveManager()->getDirection()*-1);
        if (it2 != option_directions.end()){
            option_directions.erase(it2);
        }

        std::vector<Vector2D<>> option_resulting = getFutureDirections(e, option_directions);
        if (option_resulting.empty()){
            option_resulting.push_back(e->getDirection().getOpposed());
        }

        e->getMoveManager()->makeDirection(pacman->getPosition()-e->getPosition(), option_resulting);

    }

} // Logic