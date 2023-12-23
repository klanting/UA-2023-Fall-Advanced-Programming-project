//
// Created by tibov on 22/12/23.
//

#include "WorldLoader.h"

namespace Logic::WorldLoading {
    WorldLoader::WorldLoader(std::unique_ptr<AbstractFactory> factory, const std::shared_ptr<Score>& score): factory{std::move(factory)}, score{score}{

    }
} // WorldLoading