//
// Created by tibov on 30/11/23.
//

#ifndef PROJECTPACMAN_GHOSTVIEW_H
#define PROJECTPACMAN_GHOSTVIEW_H
#include "EntityView.h"
namespace View {

    class GhostView: public EntityView{
    public:
        GhostView(std::weak_ptr<Logic::EntityModel> entity);
        void moved() override;
    private:

    };

} // View

#endif //PROJECTPACMAN_GHOSTVIEW_H
