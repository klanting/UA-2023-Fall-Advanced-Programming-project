//
// Created by tibov on 19/12/23.
//

#ifndef PROJECTPACMAN_IMAGE_H
#define PROJECTPACMAN_IMAGE_H
#include "UIObject.h"
#include <string>
namespace View {
    /**
     *This class is an derived class of UIObject
     *This is class to easily show sprites without needing to recreate it
     * */
    class Image: public UIObject{
    public:
        /**
         * Constructor for Image
         * */
        Image(const Logic::Vector2D<>& position, const Logic::Vector2D<>& size, const Logic::Vector2D<>& pixel_size, const std::shared_ptr<sf::Sprite>& sprite, const sf::Texture& texture);

        /**
         * render the image, by rendering the sprite associated with it
         * */
        void render() const override;

        /**
         * change position of image
         * */
        void setPosition(const Logic::Vector2D<>& position);

        /**
         * getter for image absolute position
         * */
        [[nodiscard]] Logic::Vector2D<> getPosition() const;

        /**
         * give a pct from 0-1 how far we want to cutoff the image only showing a part
         * */
        void cutOff(double pct) const;
    private:
        Logic::Vector2D<> pixel_size;
        std::shared_ptr<sf::Sprite> sprite;
        sf::Texture texture;

    };

} // View

#endif //PROJECTPACMAN_IMAGE_H
