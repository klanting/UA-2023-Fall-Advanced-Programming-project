//
// Created by tibov on 30/11/23.
//

#ifndef PROJECTPACMAN_ENTITYVIEW_H
#define PROJECTPACMAN_ENTITYVIEW_H
#include "../../logic/Observer.h"
#include "../../logic/Subjects/EntityModel.h"
#include "../../logic/Vector2D.h"
#include "../Camera.h"
#include <SFML/Graphics.hpp>
#include "../RenderWindowSingleton.h"
namespace View {

    /**
     * Design pattern: Observer
     * This class is an Abstract Class
     * Responsible for visualizing Entities
     * */
    template<typename T>
    class EntityView: public Logic::Observer{
    public:
        /**
         * Constructor for EntityView
         * */
        explicit EntityView(std::weak_ptr<T> entity);

        /**
         * Destructor for EntityView
         * */
        ~EntityView() override = default;

        /**
         * when the entity moves, we will draw the entity
         * */
        void moved() override;
        void consume(std::weak_ptr<Logic::EntityModel> other) override;
        void died() override;
        void finishedLvl() override;

    protected:
        /**
         * check the animation index
         * */
        void checkAnimation();
        /**
         * get the pixel value of the top position where we start loading the image we want to render
         * */
        virtual int getTop() = 0;

        /**
         * get the pixel value of the left position where we start loading the image we want to render
         * */
        virtual int getLeft();

        /**
         * entity we want to draw
         * */
        std::weak_ptr<T> entity;

        /**
         * texture that we want to draw
         * */
        sf::Texture texture;
        int animation_index;
        double animation_delay;

        int pixel_width = 40;
        int pixel_height = 40;

        int last_tick_iteration = -1;

        std::shared_ptr<sf::Sprite> sprite;

    private:

    };

} // View

#endif //PROJECTPACMAN_ENTITYVIEW_H
