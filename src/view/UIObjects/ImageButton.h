//
// Created by tibov on 28/12/23.
//

#ifndef PROJECTPACMAN_IMAGEBUTTON_H
#define PROJECTPACMAN_IMAGEBUTTON_H
#include "Button.h"
namespace View {
    /**
     * This class will be the SuperClass for all the Buttons that contain an image
     * */
    class ImageButton: public Button{
    public:
        ImageButton() = default;
        ImageButton(const Logic::Vector2D<>& position, const Logic::Vector2D<>& size);
        ImageButton(const Logic::Vector2D<>& position, const Logic::Vector2D<>& size, std::unique_ptr<Image>&& image);
        void render() const override;

    protected:
        std::unique_ptr<Image> image;

    };

} // View

#endif //PROJECTPACMAN_IMAGEBUTTON_H
