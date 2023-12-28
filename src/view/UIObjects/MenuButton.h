//
// Created by tibov on 14/12/23.
//

#ifndef PROJECTPACMAN_MENUBUTTON_H
#define PROJECTPACMAN_MENUBUTTON_H
#include "ImageButton.h"
namespace View {

    class MenuButton: public ImageButton{
    public:
        MenuButton();
        MenuButton(const Logic::Vector2D<>& position, const Logic::Vector2D<>& size);
    private:

    };

} // View

#endif //PROJECTPACMAN_MENUBUTTON_H
