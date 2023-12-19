//
// Created by tibov on 14/12/23.
//

#ifndef PROJECTPACMAN_MENUBUTTON_H
#define PROJECTPACMAN_MENUBUTTON_H
#include "Button.h"
namespace View {

    class MenuButton: public Button{
    public:
        MenuButton();
        MenuButton(const Logic::Vector2D& position, const Logic::Vector2D& size);
        void render() const override;
    private:
        std::shared_ptr<Image> image;

    };

} // View

#endif //PROJECTPACMAN_MENUBUTTON_H
