//
// Created by tibov on 14/12/23.
//

#ifndef PROJECTPACMAN_UIOBJECT_H
#define PROJECTPACMAN_UIOBJECT_H
#include "../../logic/Vector2D.h"
namespace View {

    class UIObject {
    public:
        UIObject(const Logic::Vector2D& position, const Logic::Vector2D& size);
        virtual void render() const = 0;

    protected:
        Logic::Vector2D position;
        Logic::Vector2D size;

    };

} // View

#endif //PROJECTPACMAN_UIOBJECT_H
