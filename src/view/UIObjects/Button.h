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
    /**
     *This class is an derived class of UIObject
     *This is an abstract class for UI buttons
     * It will be easy to check whether a button is clicked or not
     * */
    class Button: public UIObject{
    public:
        Button();
        Button(const Logic::Vector2D<>& position, const Logic::Vector2D<>& size);
        /**
         * check if the button is clicked based on the click position
         * the button has a position and size(from Superclass UIObject)
         * this position is still a relative position
         * We can translate it to an absolute position and size and use this to check if click_position is
         * inside this button
         * */
        virtual bool isClicked(const Logic::Vector2D<>& click_position);
        void render() const override = 0;
        ~Button() override = default;



    };

} // View

#endif //PROJECTPACMAN_BUTTON_H
