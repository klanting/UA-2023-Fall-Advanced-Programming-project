//
// Created by tibov on 23/12/23.
//

#include "CutOffAnimation.h"

namespace View {
    CutOffAnimation::CutOffAnimation(double delay, std::vector<std::unique_ptr<Image>> images, double init_delay, double wait_delay, double cutoff_change) : Animation(delay, std::move(images)), wait_delay{wait_delay}, cutoff_change{cutoff_change} {
        animation_delay += init_delay;
    }

    void CutOffAnimation::render() const {
        double d = Logic::Stopwatch::getInstance()->getDeltaTime();
        animation_delay -= d;
        while (animation_delay < 0){
            current_cutoff += cutoff_change;
            animation_delay += total_delay;

            if (current_cutoff <= 0){
                current_cutoff = 0;
                cutoff_change *= -1;

                animation_delay += wait_delay;
            }

            if (current_cutoff >= 1){
                current_cutoff = 1;
                cutoff_change *= -1;

                animation_delay += wait_delay;
            }
        }

        for (auto& m: images){
            m->cutOff(current_cutoff);
            m->render();
        }
    }
} // View