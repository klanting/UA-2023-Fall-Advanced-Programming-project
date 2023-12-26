//
// Created by tibov on 23/12/23.
//

#ifndef PROJECTPACMAN_CUTOFFANIMATION_H
#define PROJECTPACMAN_CUTOFFANIMATION_H
#include "Animation.h"
namespace View {
    /**
     * This animation will only show a part of an image
     * How much of the image is shown at a given time depends on the delay and cut_off change
     * This is used to make some cool effects (in this Project: Victory State shows the word 'Victory' that is eaten)
     * by pacman, in practice we just show less off the image showing Victory
     * */
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
