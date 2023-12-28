//
// Created by tibov on 14/12/23.
//

#ifndef PROJECTPACMAN_CONTINUEBUTTON_H
#define PROJECTPACMAN_CONTINUEBUTTON_H
#include "ImageButton.h"
namespace View {

    class ContinueButton: public ImageButton{
    public:
        ContinueButton();
        ContinueButton(const Logic::Vector2D<>& position, const Logic::Vector2D<>& size);
    private:

    };

} // View

#endif //PROJECTPACMAN_CONTINUEBUTTON_H
