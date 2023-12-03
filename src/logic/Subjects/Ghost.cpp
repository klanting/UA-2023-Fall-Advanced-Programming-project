//
// Created by tibov on 25/11/23.
//

#include "Ghost.h"
#include "../MoveStrategy/ChaseMode.h"
#include "../MoveStrategy/FearMode.h"
namespace Logic {
    Ghost::Ghost(const Vector2D &position, std::shared_ptr<Move::ModeManager> move_manager) : EntityModel(position, Vector2D{0.08,0.08}, 0.4, move_manager) {
    }

    bool Ghost::isConsumable() {
        return EntityModel::isConsumable();
    }

    void Ghost::changeMode() {
        if (consumable){
            consumable = false;
            move_manager->setStrategy(std::make_unique<Move::ChaseMode>());

            //to pacman vector is not important
            Vector2D old_direction = move_manager->getDirection();
            move_manager->makeDirection(Vector2D{1, 0}, {old_direction.getOpposed()});
        }else{
            consumable = true;
            move_manager->setStrategy(std::make_unique<Move::FearMode>());

            //to pacman vector is not important
            Vector2D old_direction = move_manager->getDirection();
            move_manager->makeDirection(Vector2D{1, 0}, {old_direction.getOpposed()});
        }
    }


} // Logic