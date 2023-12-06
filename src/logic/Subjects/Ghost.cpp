//
// Created by tibov on 25/11/23.
//

#include "Ghost.h"
#include "../MoveStrategy/ChaseMode.h"
#include "../MoveStrategy/FearMode.h"
#include <iostream>
namespace Logic {
    Ghost::Ghost(const Vector2D &position, double wait_delay, std::shared_ptr<Move::ModeManager> move_manager) : EntityModel(position, Vector2D{0.12,0.12}, 0.4,move_manager) {
        Ghost::wait_delay = wait_delay;
    }

    bool Ghost::isConsumable() {
        return EntityModel::isConsumable();
    }

    void Ghost::changeMode() {
        Vector2D old_direction = move_manager->getDirection();
        Vector2D changed = old_direction.getOpposed();
        if (wait_delay > 0){
            changed = old_direction;
        }

        if (consumable){
            consumable = false;


            move_manager->setStrategy(std::make_unique<Move::ChaseMode>());

            //to pacman vector is not important


            move_manager->makeDirection(Vector2D{1, 0}, {changed});
        }else{
            consumable = true;

            move_manager->setStrategy(std::make_unique<Move::FearMode>());

            //to pacman vector is not important

            move_manager->makeDirection(Vector2D{1, 0}, {changed});
        }
    }

    bool Ghost::handleDead(std::vector<std::shared_ptr<Subject>> others) {
        position = Vector2D{-size[0]/2, -0.5};
        consumable = false;

        move_manager->setStrategy(std::make_unique<Move::ChaseMode>());
        move_manager->makeDirection(Vector2D{1, 0}, {Vector2D{0, -1}});
        return false;
    }



} // Logic