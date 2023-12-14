//
// Created by tibov on 30/11/23.
//

#ifndef PROJECTPACMAN_WALLVIEW_H
#define PROJECTPACMAN_WALLVIEW_H
#include "EntityView.h"
#include "../../logic/Subjects/Wall.h"
namespace View {
    class WallView: public EntityView<Logic::Wall>{
    public:
        WallView(std::weak_ptr<Logic::Wall> entity);
        void moved() override;
    private:
        int getTop() override;
    };

} // View

#endif //PROJECTPACMAN_WALLVIEW_H
