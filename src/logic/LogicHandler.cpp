
#include "LogicHandler.h"
#include "Stopwatch.h"

namespace Logic {
    LogicHandler::LogicHandler(std::unique_ptr<AbstractFactory> factory){
        //clear the remaining pressed keys form the controller
        Controller::Controller::Controller::getInstance()->clear();
        difficulty_index = 1;
        score = std::make_shared<Score>();

        //makes a world and world loader
        //uncomment line below to use a WorldReader that reads files
        //world_loader = std::make_unique<WorldLoading::WorldReaderWRD>(std::move(factory), score);
        world_loader = std::make_unique<WFC::WFCGenerator>(std::move(factory), score);
        world = world_loader->load(difficulty_index, 3);

    }

    bool LogicHandler::doTick() {
        //does a tick action in the world and later updates the stopwatch
        bool alive = world->doTick();
        score->checkDecrease();
        Stopwatch::getInstance()->doTick();

        if (!alive && isGameOver()){
            HighScore::getInstance()->add(score->getScore());
        }

        return alive;
    }

    const std::shared_ptr<Score> &LogicHandler::getScore() const {
        return score;
    }

    int LogicHandler::getLives() const {
        return world->getLives();
    }

    void LogicHandler::nextLevel() {
        score->finishedLvl();
        //increases difficulty_index by 0.1 and making a new lvl
        Controller::Controller::Controller::getInstance()->clear();
        difficulty_index += 0.1;
        int remaining_lives = world->getLives();
        world = world_loader->load(difficulty_index, remaining_lives);

    }


    bool LogicHandler::isGameOver() const{
        return getLives() <= 0;
    }
} // Logic