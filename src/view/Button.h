//
// Created by tibov on 13/12/23.
//

#ifndef PROJECTPACMAN_BUTTON_H
#define PROJECTPACMAN_BUTTON_H
#include "../logic/Vector2D.h"
#include "RenderWindowSingleton.h"
namespace View {

    class Button {
    public:
        Button();
        Button(const Logic::Vector2D& position, const Logic::Vector2D& size);
        virtual bool isClicked(const Logic::Vector2D& click_position);
        virtual void render() const = 0;

    protected:
        Logic::Vector2D position;
        Logic::Vector2D size;

    };

} // View

#endif //PROJECTPACMAN_BUTTON_H
