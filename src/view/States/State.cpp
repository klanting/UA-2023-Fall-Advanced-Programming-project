

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

    void State::checkInput() {

        std::shared_ptr<RenderWindowSingleton> window = RenderWindowSingleton::getInstance();

        sf::Event event{};
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased || event.type == sf::Event::MouseButtonPressed){
                bool pressed = event.type == sf::Event::KeyPressed;
                acceptCharacter(event.key.code, pressed, Logic::Vector2D{(double) event.mouseButton.x, (double) event.mouseButton.y});
            }


            if (event.type == sf::Event::Closed){
                window->close();
            }

        }

    }
} // View