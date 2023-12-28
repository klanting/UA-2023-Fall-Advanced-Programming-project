//
// Created by tibov on 13/12/23.
//

#ifndef PROJECTPACMAN_STARTBUTTON_H
#define PROJECTPACMAN_STARTBUTTON_H
#include "ImageButton.h"

namespace View {

    class StartButton: public ImageButton{
    public:
        StartButton();
        StartButton(const Logic::Vector2D<>& position, const Logic::Vector2D<>& size);
    private:


    };

} // View

#endif //PROJECTPACMAN_STARTBUTTON_H
