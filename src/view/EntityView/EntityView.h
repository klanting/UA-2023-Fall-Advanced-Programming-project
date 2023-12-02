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
        virtual void moved() = 0;

    protected:
        std::weak_ptr<Logic::EntityModel> entity;
        sf::Sprite sprite;
        sf::Texture texture;
    private:
    };

} // View

#endif //PROJECTPACMAN_ENTITYVIEW_H
