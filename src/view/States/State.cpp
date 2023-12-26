

#include "State.h"
#include "StateManager.h"
namespace View {

    void State::setManager(const std::weak_ptr<StateManager>& state_manager_ptr) {
        State::state_manager = state_manager_ptr;
    }

    void State::renderUI() const{
        for (auto& img: render_images){
            img->render();
        }

    }
} // View