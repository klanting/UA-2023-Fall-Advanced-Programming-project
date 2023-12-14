//
// Created by tibov on 13/12/23.
//

#ifndef PROJECTPACMAN_BUTTON_H
#define PROJECTPACMAN_BUTTON_H

#include "../RenderWindowSingleton.h"
#include "UIObject.h"
namespace View {

    class Button: public UIObject{
    public:
        Button();
        Button(const Logic::Vector2D& position, const Logic::Vector2D& size);
        virtual bool isClicked(const Logic::Vector2D& click_position);
        virtual void render() const = 0;



    };

} // View

#endif //PROJECTPACMAN_BUTTON_H
