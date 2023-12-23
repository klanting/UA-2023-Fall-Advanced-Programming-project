//
// Created by tibov on 19/12/23.
//

#ifndef PROJECTPACMAN_IMAGE_H
#define PROJECTPACMAN_IMAGE_H
#include "UIObject.h"
#include <string>
namespace View {

    class Image: public UIObject{
    public:
        Image(const Logic::Vector2D& position, const Logic::Vector2D& size, const Logic::Vector2D& pixel_size, const std::shared_ptr<sf::Sprite>& sprite, const sf::Texture& texture);
        void render() const override;
        void setPosition(const Logic::Vector2D& position);
        Logic::Vector2D getPosition();
        void cutOff(double pct) const;
    private:
        Logic::Vector2D pixel_size;
        std::shared_ptr<sf::Sprite> sprite;
        sf::Texture texture;

    };

} // View

#endif //PROJECTPACMAN_IMAGE_H
