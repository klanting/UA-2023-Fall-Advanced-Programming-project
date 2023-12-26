//
// Created by tibov on 26/11/23.
//

#include "State.h"
#include "StateManager.h"
namespace View {

    void State::setManager(std::weak_ptr<StateManager> state_manager) {
        State::state_manager = state_manager;
    }

    void State::renderUI() const{
        for (auto& img: render_images){
            img->render();
        }

    }
} // View