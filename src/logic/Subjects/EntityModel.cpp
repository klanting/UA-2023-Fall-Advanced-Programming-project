//
// Created by tibov on 25/11/23.
//

#include "EntityModel.h"
#include "../MoveStrategy/PassiveMode.h"
namespace Logic {
    EntityModel::EntityModel(const Vector2D &position, double speed): Subject(position, std::make_unique<Move::PassiveMode>()), speed{0} {

    }

    EntityModel::EntityModel(const Vector2D &position, double speed, std::unique_ptr<Move::Mode> mode) : Subject(position, std::move(mode)), speed{0} {

    }

    void EntityModel::move() {
        //move function

        std::shared_ptr<Stopwatch> stopwatch= Logic::Stopwatch::getInstance();

        Vector2D direction = move_manager.getDirection();
        position += direction*stopwatch->getDeltaTime()*speed;

    }
} // Logic