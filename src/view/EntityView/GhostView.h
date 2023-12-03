//
// Created by tibov on 30/11/23.
//

#ifndef PROJECTPACMAN_GHOSTVIEW_H
#define PROJECTPACMAN_GHOSTVIEW_H
#include "EntityView.h"
namespace View {

    class GhostView: public EntityView{
    public:
        GhostView(std::weak_ptr<Logic::EntityModel> entity, int color_index);
    private:
        int getTop() override;
    };

} // View

#endif //PROJECTPACMAN_GHOSTVIEW_H
