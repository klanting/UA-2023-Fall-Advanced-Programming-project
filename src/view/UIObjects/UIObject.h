//
// Created by tibov on 14/12/23.
//

#ifndef PROJECTPACMAN_UIOBJECT_H
#define PROJECTPACMAN_UIOBJECT_H
#include "../../logic/Vector2D.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include "../RenderWindowSingleton.h"
#include "../Camera.h"
namespace View {
    /**
     *This class is an abstract class
     *This makes it easy to render all the UI components
     * */
    class UIObject {
    public:
        UIObject(const Logic::Vector2D<>& position, const Logic::Vector2D<>& size);
        /**
         * this will render the UI component
         * */
        virtual void render() const = 0;
        virtual ~UIObject() = default;

    protected:
        Logic::Vector2D<> position;
        Logic::Vector2D<> size;

    };

} // View

#endif //PROJECTPACMAN_UIOBJECT_H
