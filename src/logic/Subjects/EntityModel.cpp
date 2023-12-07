//
// Created by tibov on 25/11/23.
//

#include "EntityModel.h"
#include "../MoveStrategy/PassiveMode.h"
#include "../Observer.h"
#include <iostream>
#include <math.h>
#include <vector>
namespace Logic {


    EntityModel::EntityModel(const Vector2D &position, const Vector2D &size, double speed, std::shared_ptr<Move::ModeManager> move_manager): position{position}, speed{speed}, size{size},
                                                                                                                                             last_position{position}, start_position{position} {
        EntityModel::move_manager = move_manager;
        wait_delay = 0;
    }

    void EntityModel::move() {
        //move function


        std::shared_ptr<Stopwatch> stopwatch = Logic::Stopwatch::getInstance();
        double delta_time = stopwatch->getDeltaTime();
        if (delta_time-wait_delay < 0){
            wait_delay -= delta_time;

        }else{
            delta_time -= wait_delay;
            wait_delay = 0;

            Vector2D direction = move_manager->getDirection();

            last_position = position;

            position += direction*delta_time*speed;
        }


        for (std::shared_ptr<Observer> observer: observers){
            observer->moved();
        }

    }



    const Vector2D &EntityModel::getPosition() const {
        return position;
    }

    const Vector2D &EntityModel::getSize() const {
        return size;
    }

    std::shared_ptr<Move::ModeManager> EntityModel::getMoveManager() {
        return move_manager;
    }

    std::pair<bool, std::pair<Vector2D, Vector2D>> EntityModel::collide(std::weak_ptr<EntityModel> other) {

        if (other.expired()){
            throw "expired";
        }

        auto other_lock = other.lock();

        Vector2D center_this_last = last_position + size*0.5;
        Vector2D center_this = position + size*0.5;
        Vector2D center_other = other_lock->getPosition() + other_lock->getSize()*0.5;

        Vector2D distance = (center_this_last-center_this);

        bool collided = false;

        double best = std::numeric_limits<double>::infinity();
        int best_index = -1;
        for (int i = 0; i < 2; i++){
            bool old_between = (center_other- other_lock->getSize()*0.5)[(i+1)%2] <= (center_this_last+ size*0.5)[(i+1)%2] && (center_other + other_lock->getSize()*0.5)[(i+1)%2] >= (center_this_last- size*0.5)[(i+1)%2];
            bool new_between = (center_other- other_lock->getSize()*0.5)[(i+1)%2] <= (center_this+ size*0.5)[(i+1)%2] && (center_other + other_lock->getSize()*0.5)[(i+1)%2] >= (center_this- size*0.5)[(i+1)%2];

            if (!(old_between || new_between)){
                continue;
            }

            Vector2D change = {0, 0};
            if (distance[i] > 0){
                change = size*0.5;
            }else{
                change = size*(-0.5);
            }

            Vector2D t1 = (center_other - (other_lock->getSize()*0.5) + change - center_this)/distance;
            Vector2D t2 = (center_other + (other_lock->getSize()*0.5) + change - center_this)/distance;

            for (auto t: {t1, t2}){
                if (t[i] > 0 && t[i] < best){
                    best = t[i];
                    best_index = i;
                }
            }

        }

        if (best <= 1){
            collided = true;
        }

        Vector2D to_collision = (center_this_last*best)+center_this*(1-best);
        Vector2D bounce_direction = Vector2D{0, 0};
        if (best_index == 0){
            bounce_direction = Vector2D{1, 0};
        }else{
            bounce_direction = Vector2D{0, 1};
        }

        return std::make_pair(collided, std::make_pair(to_collision, bounce_direction));

    }

    void EntityModel::handleImpassable(std::weak_ptr<EntityModel> other, bool fix) {


        auto p = collide(other);

        if (!p.first){
            return;
        }

        Vector2D travelled = (position-last_position);
        Vector2D travelled_before_collision = (p.second.first-(last_position + size*0.5));

        Vector2D mini = std::min(move_manager->getDirection() - p.second.second, move_manager->getDirection()+ p.second.second, [](const Vector2D& a, const Vector2D& b) {return a.getLength() < b.getLength();});

        Vector2D to_do = mini*(+(travelled-travelled_before_collision));
        position -= (travelled - travelled_before_collision)*1.0001;

        if (fix){
            position += to_do;
        }


        for (std::shared_ptr<Observer> observer: observers){
            observer->moved();
        }

    }

    bool EntityModel::isConsumable() {
        return consumable;
    }

    Vector2D EntityModel::getDirection() const {
        return move_manager->getDirection();
    }

    bool EntityModel::isUp() const {
        return getDirectionIndex() == 0 || getDirection() == Vector2D{0, -1};
    }

    bool EntityModel::isDown() const {
        return getDirectionIndex() == 1 || getDirection() == Vector2D{0, 1};

    }

    bool EntityModel::isLeft() const {
        return getDirectionIndex() == 2 || getDirection() == Vector2D{-1, 0};

    }

    bool EntityModel::isRight() const {
        return getDirectionIndex() == 3 || getDirection() == Vector2D{1, 0};

    }

    void EntityModel::changeMode(bool fear) {

    }

    std::vector<Vector2D> EntityModel::splitDirection() {
        auto v = move_manager->getDirection();
        auto temp = {Vector2D{v[0], 0}, Vector2D{0, v[1]}};
        std::vector<Vector2D> output = {};

        for (auto t: temp){
            if (t == Vector2D{0, 0}){
                continue;
            }
            output.push_back(t);
        }

        return output;
    }

    bool EntityModel::handleDead(std::vector<std::shared_ptr<EntityModel>> others) {
        for (std::shared_ptr<Observer> observer: observers){
            observer->died();
        }
        return false;
    }

    EntityModel::~EntityModel() {

    }



    int EntityModel::getDirectionIndex() const{
        Vector2D change = position-last_position;
        if (change.getLength() <= 0.000001){
            return  -1;
        }

        double smallest_angle = std::numeric_limits<double>::max();
        int best_index = -1;

        std::vector<Vector2D> directions = {Vector2D{0, -1}, Vector2D{0, 1}, Vector2D{-1, 0}, Vector2D{1, 0}};

        for (int i =0; i<directions.size(); i++){
            auto v = directions[i];
            if (v.getAngle(change) < smallest_angle && v.getAngle(move_manager->getDirection()) <= M_PI/3){
                smallest_angle = v.getAngle(change);
                best_index = i;
            }

        }
        return best_index;
    }

    void EntityModel::consume(std::weak_ptr<EntityModel> other) {
        for (std::shared_ptr<Observer> observer: observers){
            observer->consume(other);
        }
    }

    void EntityModel::goStartPosition() {
        last_position = start_position;
        position = start_position;

    }

} // Logic