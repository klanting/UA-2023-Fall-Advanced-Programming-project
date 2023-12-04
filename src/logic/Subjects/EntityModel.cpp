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
    template <typename T>
    bool between(T a, T b, T c){
        //returns true if c is between a and b
        return a <= c && c <= b;
    }

    EntityModel::EntityModel(const Vector2D &position, const Vector2D &size, double speed, std::shared_ptr<Move::ModeManager> move_manager): position{position}, speed{speed}, size{size} {
        EntityModel::move_manager = move_manager;
    }

    void EntityModel::move() {
        //move function

        std::shared_ptr<Stopwatch> stopwatch= Logic::Stopwatch::getInstance();

        Vector2D direction = move_manager->getDirection();
        position += direction*stopwatch->getDeltaTime()*speed;

        for (std::shared_ptr<Observer> observer: observers){
            observer->moved();
        }

    }


    void EntityModel::addObserver(std::shared_ptr<Observer> observer) {
        observers.push_back(observer);
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

    std::pair<bool, Vector2D> EntityModel::collide(std::weak_ptr<Subject> other) {

        if (other.expired()){
            throw "expired";
        }

        Vector2D a = position;
        Vector2D b = size + a;

        Vector2D c = other.lock()->getPosition();
        Vector2D d = other.lock()->getSize() + c;

        std::vector<Vector2D> baselines = {Vector2D{1, 0}, Vector2D{0, 1}};
        bool collided = true;
        Vector2D max_overlap = Vector2D{0, 0};
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

            std::vector<Vector2D> distances = {d_c-a_c, c_c-b_c};

            Vector2D dir = move_manager->getDirection().projection(baseline);

            auto index = std::min_element(distances.begin(), distances.end(), [&dir](const Vector2D& a, const Vector2D& b){return a.getLength() < b.getLength();});
            max_overlap += *index;

        }


        return std::make_pair(collided, max_overlap);
    }

    void EntityModel::handleImpassable(std::weak_ptr<Subject> other) {

        auto p = collide(other);

        other.lock()->debug_green = true;

        if (!p.first){
            return;
        }

        position += p.second.projection(move_manager->getDirection())*1.000001;


    }

    bool EntityModel::isConsumable() {
        return consumable;
    }

    Vector2D EntityModel::getDirection() const {
        return move_manager->getDirection();
    }

    bool EntityModel::isUp() const {
        return getDirection() == Vector2D{0, -1};
    }

    bool EntityModel::isDown() const {
        return getDirection() == Vector2D{0, 1};
    }

    bool EntityModel::isLeft() const {
        return getDirection() == Vector2D{-1, 0};
    }

    bool EntityModel::isRight() const {
        return getDirection() == Vector2D{1, 0};
    }

    void EntityModel::changeMode() {

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

} // Logic