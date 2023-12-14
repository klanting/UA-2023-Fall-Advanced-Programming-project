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
        ContinueButton(const Logic::Vector2D& position, const Logic::Vector2D& size);
        void render() const override;
    private:
        sf::Texture texture;
        std::shared_ptr<sf::Sprite> button_print;

    };

} // View

#endif //PROJECTPACMAN_CONTINUEBUTTON_H
