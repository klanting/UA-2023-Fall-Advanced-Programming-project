//
// Created by tibov on 13/12/23.
//

#ifndef PROJECTPACMAN_BUTTON_H
#define PROJECTPACMAN_BUTTON_H

#include "../RenderWindowSingleton.h"
#include "UIObject.h"
#include "../Camera.h"
#include "Image.h"
namespace View {

    class Button: public UIObject{
    public:
        Button();
        Button(const Logic::Vector2D<>& position, const Logic::Vector2D<>& size);
        virtual bool isClicked(const Logic::Vector2D<>& click_position);
        void render() const override = 0;
        ~Button() override = default;



    };

} // View

#endif //PROJECTPACMAN_BUTTON_H
