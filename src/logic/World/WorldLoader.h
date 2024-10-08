//
// Created by tibov on 22/12/23.
//

#ifndef PROJECTPACMAN_WORLDLOADER_H
#define PROJECTPACMAN_WORLDLOADER_H
#include <memory>
#include "../Subjects/EntityModel.h"
#include "../AbstractFactory.h"
#include "World.h"

namespace Logic::WorldLoading {

    /**
         * Design Pattern: Abstract Factory
         * Abstract class for WorldLoading
         * */
    class WorldLoader {
    public:
        /**
         * Constructor for WorldLoader
         * */
        WorldLoader(std::unique_ptr<AbstractFactory>&& factory, const std::shared_ptr<Score>& score);
        virtual ~WorldLoader() = default;

        /**
         * Load function will create a new World
         * */
        virtual std::unique_ptr<World> load(double difficulty, int lives) = 0;

    protected:
        std::unique_ptr<AbstractFactory> factory;
        std::shared_ptr<Score> score;



    };

} // Logic::WorldLoading

#endif //PROJECTPACMAN_WORLDLOADER_H
