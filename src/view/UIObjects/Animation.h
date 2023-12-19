//
// Created by tibov on 19/12/23.
//

#ifndef PROJECTPACMAN_ANIMATION_H
#define PROJECTPACMAN_ANIMATION_H
#include "UIObject.h"
#include "Image.h"
namespace View {

    class Animation: public UIObject{
    public:
        Animation(const Logic::Vector2D& position, const Logic::Vector2D& size, double delay, std::vector<std::unique_ptr<Image>> images);
        virtual void render() const override = 0;
    protected:
        mutable double animation_delay = 0.5;
        std::vector<std::unique_ptr<Image>> images;


    };

} // View

#endif //PROJECTPACMAN_ANIMATION_H
