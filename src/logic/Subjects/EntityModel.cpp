//
// Created by tibov on 25/11/23.
//

#include "EntityModel.h"
#include "../MoveStrategy/PassiveMode.h"
namespace Logic {
    EntityModel::EntityModel(const Vector2D &position, double speed): Subject(position, std::make_unique<Move::PassiveMode>()), speed{speed} {

    }

    EntityModel::EntityModel(const Vector2D &position, double speed, std::unique_ptr<Move::Mode> mode) : Subject(position, std::move(mode)), speed{speed} {

    }

    void EntityModel::move() {
        //move function

        std::shared_ptr<Stopwatch> stopwatch= Logic::Stopwatch::getInstance();

        Vector2D direction = move_manager.getDirection();
        position += direction*stopwatch->getDeltaTime()*speed;

    }

    void EntityModel::calculateDirection(const Vector2D &to_pacman, const std::vector<Vector2D> &options) {
        move_manager.makeDirection(to_pacman, options);

    }

    void EntityModel::addObserver(std::shared_ptr<Observer> observer) {
        observers.push_back(observer);
    }
} // Logic