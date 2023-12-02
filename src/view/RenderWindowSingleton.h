//
// Created by tibov on 02/12/23.
//

#ifndef PROJECTPACMAN_RENDERWINDOWSINGLETON_H
#define PROJECTPACMAN_RENDERWINDOWSINGLETON_H
#include <memory>
#include <SFML/Graphics.hpp>
namespace View {
    typedef sf::RenderWindow RW;
    class RenderWindowSingleton {
    public:
        static std::shared_ptr<RenderWindowSingleton> getInstance();

        const std::shared_ptr<RW> &getWindow() const;

    private:
        RenderWindowSingleton();
        inline static std::shared_ptr<RenderWindowSingleton> _instance;
        std::shared_ptr<RW> window;
    };

} // View

#endif //PROJECTPACMAN_RENDERWINDOWSINGLETON_H
