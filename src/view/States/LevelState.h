//
// Created by tibov on 26/11/23.
//

#ifndef PROJECTPACMAN_LEVELSTATE_H
#define PROJECTPACMAN_LEVELSTATE_H
#include "State.h"
#include "../../logic/World.h"
namespace View {

    class LevelState: public State{
    public:
        LevelState();
        void runTick() override;
        void acceptCharacter(char input) override;
    private:
        std::unique_ptr<Logic::World> world;

    };

} // View

#endif //PROJECTPACMAN_LEVELSTATE_H
