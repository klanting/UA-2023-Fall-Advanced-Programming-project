//
// Created by tibov on 02/12/23.
//

#include "RenderWindowSingleton.h"

namespace View {
    std::shared_ptr<RenderWindowSingleton > RenderWindowSingleton::getInstance() {
        if (!_instance){
            _instance = std::shared_ptr<RenderWindowSingleton >(new RenderWindowSingleton);
        }
        return _instance;
    }

    RenderWindowSingleton::RenderWindowSingleton() {
        window = std::make_shared<RW>(sf::VideoMode(1000, 1000), "Pacman");
    }

    const std::shared_ptr<RW> &RenderWindowSingleton::getWindow() const {
        return window;
    }
} // View