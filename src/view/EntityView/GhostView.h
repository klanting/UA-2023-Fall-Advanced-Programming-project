//
// Created by tibov on 30/11/23.
//

#ifndef PROJECTPACMAN_GHOSTVIEW_H
#define PROJECTPACMAN_GHOSTVIEW_H
#include "EntityView.h"
namespace View {

    class GhostView: public EntityView{
    public:
        void update(std::shared_ptr<Logic::Subject> subject) override;
    private:

    };

} // View

#endif //PROJECTPACMAN_GHOSTVIEW_H
