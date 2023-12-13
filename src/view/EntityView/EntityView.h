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

    class EntityView: public Logic::Observer{
    public:
        EntityView(std::weak_ptr<Logic::EntityModel> entity);
        virtual void moved();
        void consume(std::weak_ptr<Logic::EntityModel> other) override;
        void died() override;
        void finishedLvl() override;

    protected:
        void checkAnimation();
        virtual int getTop() = 0;
        virtual int getLeft();

        std::weak_ptr<Logic::EntityModel> entity;

        sf::Texture texture;
        int animation_index;
        double animation_delay;

        int pixel_width = 40;
        int pixel_height = 40;

        int last_tick_iteration = -1;

    private:

    };

} // View

#endif //PROJECTPACMAN_ENTITYVIEW_H
