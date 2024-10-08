//
// Created by tibov on 22/12/23.
//

#ifndef PROJECTPACMAN_WORLDREADER_H
#define PROJECTPACMAN_WORLDREADER_H
#include "WorldLoader.h"

namespace Logic::WorldLoading {

    /**
         * part of Design Pattern: abstract Factory
         * Abstract Class for all worldLoaders that read a world file
         * */
    class WorldReader: public WorldLoader{
    public:
        WorldReader(std::unique_ptr<AbstractFactory>&& factory, const std::shared_ptr<Score>& score);
        std::unique_ptr<World> load(double difficulty, int lives) override = 0;
    private:
    };

} // Logic::WorldLoading


#endif //PROJECTPACMAN_WORLDREADER_H
