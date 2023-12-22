//
// Created by tibov on 22/12/23.
//

#ifndef PROJECTPACMAN_WORLDREADER_H
#define PROJECTPACMAN_WORLDREADER_H
#include "WorldLoader.h"

namespace Logic::WorldLoading {

    class WorldReader: public WorldLoader{
    public:
        WorldReader(const std::shared_ptr<AbstractFactory>& factory);
        WorldData load() override;
    private:
    };

} // Logic::WorldLoading


#endif //PROJECTPACMAN_WORLDREADER_H
