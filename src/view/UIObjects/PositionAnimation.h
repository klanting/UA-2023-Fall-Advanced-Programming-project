//
// Created by tibov on 19/12/23.
//

#ifndef PROJECTPACMAN_POSITIONANIMATION_H
#define PROJECTPACMAN_POSITIONANIMATION_H
#include "Animation.h"
namespace View {

    class PositionAnimation: public Animation{
    public:
        PositionAnimation(const Logic::Vector2D& position, const Logic::Vector2D& size, double delay, std::vector<std::unique_ptr<Image>> images, double left_bound, double right_bound);
        void render() const override;
    private:
        double left_bound = -1;
        double right_bound = 1;

        mutable double animation_position = -0.9;
        mutable int animation_direction = 1;
        std::vector<std::unique_ptr<Image>> images;

    };

} // View

#endif //PROJECTPACMAN_POSITIONANIMATION_H
