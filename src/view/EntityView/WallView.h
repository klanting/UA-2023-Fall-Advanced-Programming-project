//
// Created by tibov on 30/11/23.
//

#ifndef PROJECTPACMAN_WALLVIEW_H
#define PROJECTPACMAN_WALLVIEW_H
#include "EntityView.h"
namespace View {

    class WallView: public EntityView{
    public:
        void update(std::shared_ptr<Logic::Subject> subject) override;
    private:
    };

} // View

#endif //PROJECTPACMAN_WALLVIEW_H
