//
// Created by tibov on 25/11/23.
//

#ifndef PROJECTPACMAN_LOGICHANDLER_H
#define PROJECTPACMAN_LOGICHANDLER_H
#include "AbstractFactory.h"
#include "World/World.h"
#include "Controller/Controller.h"
#include "Controller/Controller.h"
#include "Score.h"
#include "../logic/World/WorldReader.h"
namespace Logic {

    /**
     * This Class will be in between the LevelState and the WorldState
     * This will manage the World object and change it if needed
     * */
    class LogicHandler {
    public:
        /**
         * Constructor for logicHandler
         * */
        explicit LogicHandler(std::unique_ptr<AbstractFactory> factory);

        /**
         * Destructor for logicHandler
         * */
        ~LogicHandler() = default;

        /**
         * Will do the actions of 1 tick
         * */
        bool doTick();

        /**
         * Getter for Score Observer
         * */
        [[nodiscard]] const std::shared_ptr<Score> &getScore() const;

        /**
         * Getter for remaining amount of lives
         * */
        [[nodiscard]] int getLives() const;

        /**
         * A new level will be created
         * */
        void nextLevel();

        /**
         * This will be true if the game is Game OVer (lost)
         * */
        [[nodiscard]] bool isGameOver() const;
    private:
        /**
         * ptr to world currently in use
         * */
        std::unique_ptr<Logic::World> world;

        /**
         * This will store a worldLoader to load/reload the world
         * */
        std::unique_ptr<WorldLoading::WorldLoader> world_loader;

        /**
         * Stores score observer
         * */
        std::shared_ptr<Score> score;

        /**
         * stores current difficult index starts with 1.0, increasing it will make the game more difficult
         * */
        double difficulty_index;
    };

} // Logic

#endif //PROJECTPACMAN_LOGICHANDLER_H
