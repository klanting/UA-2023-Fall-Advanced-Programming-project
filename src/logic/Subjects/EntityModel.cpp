//
// Created by tibov on 25/11/23.
//

#include "EntityModel.h"
#include "../MoveStrategy/PassiveMode.h"
#include "../Observer.h"
#include <iostream>
namespace Logic {
    template <typename T>
    bool between(T a, T b, T c){
        //returns true if c is between a and b
        return a <= c && c <= b;
    }

    EntityModel::EntityModel(const Vector2D &position, double speed, std::shared_ptr<Move::ModeManager> move_manager): position{position}, speed{speed}, size{Vector2D{0.05, 0.05}} {
        EntityModel::move_manager = move_manager;
    }

    void EntityModel::move() {
        //move function

        std::shared_ptr<Stopwatch> stopwatch= Logic::Stopwatch::getInstance();

        Vector2D direction = move_manager->getDirection();
        double d = stopwatch->getDeltaTime();
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

    bool EntityModel::collide(std::weak_ptr<Subject> other) {

        if (other.expired()){
            throw "expired";
        }

        Vector2D a = position;
        Vector2D b = size + a;

        Vector2D c = other.lock()->getPosition();
        Vector2D d = other.lock()->getSize() + c;


        std::vector<Vector2D> baselines = {Vector2D{1, 0}, Vector2D{0, 1}};
        bool collided = true;
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
        }

        return collided;
    }


} // Logic