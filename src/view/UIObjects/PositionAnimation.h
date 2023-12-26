//
// Created by tibov on 22/12/23.
//

#ifndef PROJECTPACMAN_POSITIONANIMATION_H
#define PROJECTPACMAN_POSITIONANIMATION_H
#include "ImageAnimation.h"
#include "Image.h"
namespace View {
    /**
     * This class is a derived class of ImageAnimation
     * This will move the animated image to another location
     * */
    class PositionAnimation: public ImageAnimation{
    public:
        /**
         * Constructor Position Animation
         * */
        PositionAnimation(double delay, std::vector<std::unique_ptr<Image>> images, const Logic::Vector2D<>& from, const Logic::Vector2D<>& to);
        void render() const override;
    private:
        /**
         * value for linear interpolation between start and end position
         * */
        mutable double animation_position = 0;
        /**
         * goes one way till end_position and than the other way till back to start position
         * */
        mutable int animation_direction = 1;
        /**
         * start position
         * */
        Logic::Vector2D<> start_position;

        /**
         * end position
         * */
        Logic::Vector2D<> end_position;

    };

} // View

#endif //PROJECTPACMAN_POSITIONANIMATION_H
