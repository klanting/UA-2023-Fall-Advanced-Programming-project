//
// Created by tibov on 02/12/23.
//

#ifndef PROJECTPACMAN_RENDERWINDOWSINGLETON_H
#define PROJECTPACMAN_RENDERWINDOWSINGLETON_H
#include <memory>
#include <SFML/Graphics.hpp>
#include "../logic/Subjects/EntityModel.h"
namespace View {
    /**
     * Design pattern: Singleton
     * This class is a wrapper for the SFML window
     * This will store buffers of thinks needed to be drawn
     * To prevent that we draw an entity double within the same Tick
     * This buffer will make sure to override the original drawing
     * */
    typedef sf::RenderWindow RW;
    class RenderWindowSingleton {
    public:
        static std::shared_ptr<RenderWindowSingleton> getInstance();

        /**
         * Stores Drawable in buffer with the entity as key
         * */
        void draw(const std::weak_ptr<Logic::EntityModel>& e, std::shared_ptr<sf::Drawable> s);

        /**
         * draws the drawable bypassing the buffer
         * */
        void drawBufferless(const std::shared_ptr<sf::Drawable>& s);

        /**
         * returns if the window is open
         * */
        bool isOpen();

        /**
         * do the pollEvent of the window
         * */
        bool pollEvent(sf::Event& event);

        /**
         * does window.display
         * */
        void display();

        /**
         * closes the window
         * */
        void close();

        /**
         * clears the window
         * */
        void clear();

        /**
         * getter for window size
         * */
        [[nodiscard]] sf::Vector2<unsigned int> getSize() const;

    private:
        RenderWindowSingleton();
        inline static std::shared_ptr<RenderWindowSingleton> _instance;
        std::unique_ptr<RW> window;

        std::map<std::shared_ptr<Logic::EntityModel>, std::shared_ptr<sf::Drawable>> draw_buffer;
    };

} // View

#endif //PROJECTPACMAN_RENDERWINDOWSINGLETON_H
