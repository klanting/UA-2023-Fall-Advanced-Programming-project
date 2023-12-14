//
// Created by tibov on 02/12/23.
//

#ifndef PROJECTPACMAN_RENDERWINDOWSINGLETON_H
#define PROJECTPACMAN_RENDERWINDOWSINGLETON_H
#include <memory>
#include <SFML/Graphics.hpp>
#include "../logic/Subjects/EntityModel.h"
namespace View {
    typedef sf::RenderWindow RW;
    class RenderWindowSingleton {
    public:
        static std::shared_ptr<RenderWindowSingleton> getInstance();

        //const std::shared_ptr<RW> &getWindow() const;
        void draw(std::weak_ptr<Logic::EntityModel> e, std::shared_ptr<sf::Drawable> s);
        void draw_bufferless(std::unique_ptr<sf::Drawable> s);
        bool isOpen();
        bool pollEvent(sf::Event& event);
        void display();
        void close();
        void clear();
        sf::Vector2<unsigned int> getSize();

    private:
        RenderWindowSingleton();
        inline static std::shared_ptr<RenderWindowSingleton> _instance;
        std::unique_ptr<RW> window;

        std::map<std::shared_ptr<Logic::EntityModel>, std::shared_ptr<sf::Drawable>> draw_buffer;
    };

} // View

#endif //PROJECTPACMAN_RENDERWINDOWSINGLETON_H
