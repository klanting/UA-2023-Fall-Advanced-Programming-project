//
// Created by tibov on 23/12/23.
//

#ifndef PROJECTPACMAN_CUTOFFANIMATION_H
#define PROJECTPACMAN_CUTOFFANIMATION_H
#include "Animation.h"
namespace View {

    class CutOffAnimation: public Animation{
    public:
        CutOffAnimation(double delay, std::vector<std::unique_ptr<Image>> images, double init_delay, double wait_delay, double cutoff_change);
        void render() const override;
    private:
        mutable double current_cutoff;
        mutable double cutoff_change = 0.1;
        double wait_delay;

    };

} // View

#endif //PROJECTPACMAN_CUTOFFANIMATION_H
