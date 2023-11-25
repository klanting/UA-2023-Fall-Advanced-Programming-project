//
// Created by tibov on 25/11/23.
//

#include "EntityModel.h"
#include "../MoveStrategy/PassiveMode.h"
namespace Logic {
    EntityModel::EntityModel(const Vector2D &position): Subject(position, std::make_unique<Move::PassiveMode>()) {

    }

    EntityModel::EntityModel(const Vector2D &position, std::unique_ptr<Move::Mode> mode) : Subject(position, std::move(mode)) {

    }

    void EntityModel::move() {
        //move function
        //still need to take stopwatch into account

        Vector2D direction = move_manager.getDirection();
        position += direction;

    }
} // Logic