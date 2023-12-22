//
// Created by tibov on 22/12/23.
//

#include "WorldReader.h"

namespace Logic::WorldLoading {
    WorldData WorldReader::load() {
        WorldData output;

        return output;
    }

    WorldReader::WorldReader(const std::shared_ptr<AbstractFactory> &factory) : WorldLoader(factory) {

    }
} // Logic::WorldLoading