//
// Created by tibov on 13/12/23.
//

#ifndef PROJECTPACMAN_STARTBUTTON_H
#define PROJECTPACMAN_STARTBUTTON_H
#include "Button.h"

namespace View {

    class StartButton: public Button{
    public:
        StartButton();
        StartButton(const Logic::Vector2D<>& position, const Logic::Vector2D<>& size);
        void render() const override;
    private:
        std::shared_ptr<Image> image;


    };

} // View

#endif //PROJECTPACMAN_STARTBUTTON_H
