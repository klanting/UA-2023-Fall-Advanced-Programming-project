//
// Created by tibov on 25/11/23.
//

#include "World.h"
#include "fstream"
#include "iostream"
#include "functional"


namespace Logic {

    World::World(const std::shared_ptr<EntityModel>& pacman, const std::vector<std::shared_ptr<EntityModel>>& entities,
    const std::vector<std::shared_ptr<EntityModel>>& not_passable, const std::vector<std::shared_ptr<EntityModel>>& intersection,
    int lives, int consumable_count) {
        World::lives = lives;
        World::pacman = pacman;
        World::entities = entities;
        World::not_passable = not_passable;
        World::intersection = intersection;
        World::consumable_count = consumable_count;

    }

    std::vector<std::weak_ptr<EntityModel>> World::checkCollision(std::shared_ptr<EntityModel> s, int type) {
        std::vector<std::weak_ptr<EntityModel>> hits;

        auto to_check = entities;
        if (type == 1){
            to_check = not_passable;
        }else if (type == 2){
            to_check = intersection;
        }

        for (std::shared_ptr<EntityModel> other: to_check){
            if (s == other){
                continue;
            }

            auto p = s->collide(other);
            if (p.first){
                hits.push_back(other);
            }

        }
        return hits;
    }

    bool World::doTick() {
        to_be_removed.clear();

        for (auto& e: entities){
            e->move();
            handleInPassable(e);

            handleHit(e);

            handleIntersection(e);


        }

        for (auto e: to_be_removed){
            auto it = std::find(entities.begin(), entities.end(), e.lock());
            entities.erase(it);
            consumable_count -=1;
        }

        for (auto i: intersection){
            i->move();
        }

        bool alive = lives > 0;
        bool still_food = consumable_count > 0;

        return alive && still_food;

    }

    void World::handleInPassable(std::shared_ptr<EntityModel> e) {

        bool hit_wall = false;
        bool fix = true;
        for (int  i=0; i<2; i++){
            std::vector<std::weak_ptr<EntityModel>> np;
            std::vector<std::weak_ptr<EntityModel>> hits = checkCollision(e, 1);

            if (hits.empty()){
                break;
            }


            for (auto hit: hits){
                e->handleInpassable(hit, fix);
                hit_wall = true;
                np.push_back(hit);
            }


            fix = false;

        }

        if (hit_wall){

            std::vector<Vector2D> option_directions = {Vector2D{0,1}, Vector2D{0,-1}, Vector2D{1,0}, Vector2D{-1,0}};
            auto it = std::find(option_directions.begin(), option_directions.end(), e->getMoveManager()->getDirection());
            if (it != option_directions.end()){
                option_directions.erase(it);
            }
            auto it2 = std::find(option_directions.begin(), option_directions.end(), e->getMoveManager()->getDirection()*-1);
            if (it2 != option_directions.end()){
                option_directions.erase(it2);
            }

            std::vector<Vector2D> option_resulting = getFutureDirections(e, option_directions);
            if (option_resulting.empty()){
                option_resulting.push_back(e->getDirection().getOpposed());
            }

            e->getMoveManager()->makeDirection(pacman->getPosition()-e->getPosition(), option_resulting);

        }

    }

    void World::handleActionsPacman(std::shared_ptr<EntityModel> e, std::weak_ptr<EntityModel> hit) {

        if (hit.lock()->isConsumable()){
            e->consume(hit);
            if (hit.lock()->handleDead(entities)){
                to_be_removed.push_back(hit);
            }

        } else{
            e->handleDead(entities);
            lives -= 1;

            if (lives == 0){
                std::cout << "game over" << std::endl;
            }
        }

    }

    void World::handleActions(std::shared_ptr<EntityModel> e, std::weak_ptr<EntityModel> hit) {
        //make sure only ghosts do this
        if (hit.lock() == pacman){
            handleActionsPacman(hit.lock(), e);

        }

    }

    int World::getLives() const {
        return lives;
    }

    void World::handleHit(std::shared_ptr<EntityModel> e) {
        using ColHandle = void (World::*)(std::shared_ptr<EntityModel>, std::weak_ptr<EntityModel>);
        ColHandle func;
        if (e == pacman){
            func = &World::handleActionsPacman;
        }else{
            func = &World::handleActions;
        }

        std::vector<std::weak_ptr<EntityModel>> hits = checkCollision(e);
        for (auto hit: hits){
            (this->*func)(e, hit);
        }

    }

    std::vector<Vector2D>
    World::getFutureDirections(std::shared_ptr<EntityModel> e, const std::vector<Vector2D> &options) {
        std::vector<Vector2D> option_resulting = {};
        for (auto o: options){


            Vector2D resultPos = e->getPosition()+o*0.05;
            bool walkable = true;
            for (auto np: not_passable){
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

    void World::handleIntersection(std::shared_ptr<EntityModel> e) {
        std::vector<std::weak_ptr<EntityModel>> hits_intersection = checkCollision(e, 2);
        for (auto hit: hits_intersection){
            auto it = last_intersection.find(e);
            if (it != last_intersection.end()){
                if (it->second == hit.lock()){
                    //only care if we are inside the intersection
                    Vector2D center = e->getPosition()+e->getSize()*0.5;
                    Vector2D inter_cent = hit.lock()->getPosition()+hit.lock()->getSize()*0.5;
                    if (center.getDistance(inter_cent) > (hit.lock()->getSize()*0.5)[0]){
                        continue;
                    }
                    e->handleInpassable(hit, false);
                    Vector2D old_dir = e->getDirection();
                    std::vector<Vector2D> option_directions = {old_dir.rotate(M_PI/2.0), old_dir.rotate(-1*M_PI/2.0), old_dir};
                    std::vector<Vector2D> resulting = getFutureDirections(e, option_directions);
                    e->getMoveManager()->makeDirection(pacman->getPosition()-e->getPosition(), resulting);
                    last_intersection.erase(it);
                    continue;

                }
            }
            if (it != last_intersection.end()){
                it->second = hit.lock();
            }else{
                last_intersection.insert({e, hit.lock()});
            }
        }

    }


} // Logic