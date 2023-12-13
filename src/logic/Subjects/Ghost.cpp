//
// Created by tibov on 25/11/23.
//

#include "Ghost.h"
#include "../MoveStrategy/ChaseMode.h"
#include "../MoveStrategy/FearMode.h"
#include <iostream>
namespace Logic {
    Ghost::Ghost(const Vector2D &position, double wait_delay, std::shared_ptr<Move::ModeManager> move_manager, double difficulty) : EntityModel(position, Vector2D{0.12,0.12}, 0.4*difficulty, move_manager) {
        Ghost::wait_delay = wait_delay;
        total_fear_time = 8/difficulty;
    }

    bool Ghost::isConsumable() {
        return EntityModel::isConsumable();
    }

    void Ghost::changeMode(bool fear) {
        Vector2D old_direction = move_manager->getDirection();
        Vector2D changed = old_direction.getOpposed();
        if (wait_delay > 0){
            changed = old_direction;
        }


        if (consumable && !fear){
            consumable = false;


            move_manager->setStrategy(std::make_unique<Move::ChaseMode>());

            //to pacman vector is not important


            move_manager->makeDirection(Vector2D{2, 2}, {changed});
        }else if (!consumable && fear){
            consumable = true;
            fear_time = total_fear_time;

            move_manager->setStrategy(std::make_unique<Move::FearMode>());

            //to pacman vector is not important

            move_manager->makeDirection(Vector2D{2, 2}, {changed});

        }else if(fear){
            fear_time = total_fear_time;
        }

    }

    bool Ghost::handleDead(std::vector<std::shared_ptr<EntityModel>> others) {
        EntityModel::handleDead(others);

        EntityModel::goStartPosition();
        consumable = false;

        move_manager->setStrategy(std::make_unique<Move::ChaseMode>());
        move_manager->makeDirection(Vector2D{2, 2}, {Vector2D{0, -1}});
        return false;
    }

    void Ghost::goStartPosition() {
        EntityModel::goStartPosition();
        move_manager->makeDirection(Vector2D{2, 2}, {Vector2D{0, -1}});
    }

    void Ghost::move() {
        EntityModel::move();
        if (consumable){
            fear_time -= Stopwatch::getInstance()->getDeltaTime();
            if (fear_time < 0){
                fear_time = 0;
                changeMode(false);
            }
        }
    }

    bool Ghost::AlmostChase() const{
        return fear_time < 3;
    }

    int Ghost::bonus() const {
        return 200;
    }


} // Logic