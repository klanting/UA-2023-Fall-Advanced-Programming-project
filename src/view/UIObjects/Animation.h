//
// Created by tibov on 19/12/23.
//

#ifndef PROJECTPACMAN_ANIMATION_H
#define PROJECTPACMAN_ANIMATION_H
#include "UIObject.h"
#include "Image.h"
namespace View {
    /**
     *This class is an derived class of UIObject
     *This is an abstract class for UI Animations, this animations will work independent of other objects and
     * will be based on a animation delay
     * The Animation class will receive a vector of images this is so the animation can alternate between images
     * */
    class Animation: public UIObject{
    public:
        Animation(double delay, std::vector<std::unique_ptr<Image>> images);

        /**
         * pure virtual function for rendering the animation
         * */
        void render() const override = 0;
        ~Animation() override = default;

    protected:
        /**
         * animation delay is mutable because this delay will be able to be changed during the const render function
         * */
        mutable double animation_delay = 0.5;
        double total_delay = 0.5;
        std::vector<std::unique_ptr<Image>> images;


    };

} // View

#endif //PROJECTPACMAN_ANIMATION_H
