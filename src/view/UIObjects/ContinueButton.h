//
// Created by tibov on 14/12/23.
//

#ifndef PROJECTPACMAN_CONTINUEBUTTON_H
#define PROJECTPACMAN_CONTINUEBUTTON_H
#include "Button.h"
namespace View {

    class ContinueButton: public Button{
    public:
        ContinueButton();
        ContinueButton(const Logic::Vector2D<>& position, const Logic::Vector2D<>& size);
        void render() const override;
    private:
        std::shared_ptr<Image> image;

    };

} // View

#endif //PROJECTPACMAN_CONTINUEBUTTON_H
