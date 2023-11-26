//
// Created by tibov on 26/11/23.
//

#include "LevelState.h"

namespace View {
    LevelState::LevelState() {
        world = std::make_unique<Logic::World>();

    }
} // View