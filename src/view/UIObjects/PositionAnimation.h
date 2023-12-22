//
// Created by tibov on 22/12/23.
//

#ifndef PROJECTPACMAN_POSITIONANIMATION_H
#define PROJECTPACMAN_POSITIONANIMATION_H
#include "Animation.h"
#include "Image.h"
namespace View {

    class PositionAnimation: public Animation{
    public:
        PositionAnimation(double delay, std::vector<std::unique_ptr<Image>> images, const Logic::Vector2D& from, const Logic::Vector2D& to);
        void render() const override;
    private:
        mutable double animation_position = 0;
        mutable int animation_direction = 1;
        Logic::Vector2D start_position;
        Logic::Vector2D end_position;

    };

} // View

#endif //PROJECTPACMAN_POSITIONANIMATION_H
