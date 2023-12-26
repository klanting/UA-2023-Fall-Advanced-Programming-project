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
        Animation(double delay, std::vector<std::unique_ptr<Image>> images);
        void render() const override = 0;
        ~Animation() override = default;

    protected:
        mutable double animation_delay = 0.5;
        double total_delay = 0.5;
        std::vector<std::unique_ptr<Image>> images;


    };

} // View

#endif //PROJECTPACMAN_ANIMATION_H
