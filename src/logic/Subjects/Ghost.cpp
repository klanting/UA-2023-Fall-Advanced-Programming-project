//
// Created by tibov on 25/11/23.
//

#include "Ghost.h"
#include "../MoveStrategy/ChaseMode.h"
#include "../MoveStrategy/FearMode.h"
#include <iostream>
namespace Logic {
    Ghost::Ghost(const Vector2D<> &position, double wait_delay, const std::shared_ptr<Move::ModeManager>& move_manager, double difficulty) : EntityModel(position, Vector2D{0.12,0.12}, 0.4*difficulty, move_manager) {
        //initialize data members
        Ghost::wait_delay = wait_delay;
        total_fear_time = 8.0/difficulty;
        fear_time = 0;
    }

    bool Ghost::isConsumable() const{
        return EntityModel::isConsumable();
    }

    void Ghost::changeMode(bool fear) {
        Vector2D old_direction = move_manager->getDirection();
        Vector2D changed = old_direction.getOpposed();
        if (wait_delay > 0){
            changed = old_direction;
        }


        if (consumable && !fear){
            //here is when fear mode ends
            //we will make sure to put the Ghost back in ChaseMode
            consumable = false;
            speed = speed/0.8;

            move_manager->setStrategy(std::make_unique<Move::ChaseMode>());
            move_manager->makeDirection(Vector2D<>{2, 2}, {changed});
        }else if (!consumable && fear){
            //here is when we enter fear mode
            //we will set the mode to Fear Mode
            consumable = true;
            fear_time = total_fear_time;
            speed = speed*0.8;

            move_manager->setStrategy(std::make_unique<Move::FearMode>());
            move_manager->makeDirection(Vector2D<>{2, 2}, {changed});

        }else if(fear){
            //if it was already in fear mode we will not change anything except resetting the time till fear mode tends
            fear_time = total_fear_time;
        }

    }

    bool Ghost::handleDead(const std::vector<std::shared_ptr<EntityModel>>& others) {
        //on dead go back in Chase mode
        EntityModel::handleDead(others);

        Ghost::goStartPosition();
        consumable = false;

        move_manager->setStrategy(std::make_unique<Move::ChaseMode>());
        move_manager->makeDirection(Vector2D<>{2, 2}, {Vector2D<>{0, -1}});
        return false;
    }

    void Ghost::goStartPosition() {
        EntityModel::goStartPosition();

        //delay to prevent all ghosts being inside each other at the start
        double d = Random::getInstance()->getRandom();
        wait_delay += d;

        move_manager->makeDirection(Vector2D<>{2, 2}, {Vector2D<>{0, -1}});
    }

    void Ghost::move() {
        EntityModel::move();

        //if in fear mode check whether we need to go back to Normal(ChaseMode)
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