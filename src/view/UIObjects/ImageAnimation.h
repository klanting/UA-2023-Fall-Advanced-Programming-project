//
// Created by tibov on 19/12/23.
//

#ifndef PROJECTPACMAN_IMAGEANIMATION_H
#define PROJECTPACMAN_IMAGEANIMATION_H
#include "Animation.h"
#include "Image.h"
namespace View {

    class ImageAnimation: public Animation{
    public:
        ImageAnimation(double delay, std::vector<std::unique_ptr<Image>> images);
        void render() const override;

    protected:
        mutable int animation_index = 0;


    };

} // View

#endif //PROJECTPACMAN_IMAGEANIMATION_H
