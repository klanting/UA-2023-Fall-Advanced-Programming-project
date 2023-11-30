//
// Created by tibov on 30/11/23.
//

#ifndef PROJECTPACMAN_PACMANVIEW_H
#define PROJECTPACMAN_PACMANVIEW_H
#include "EntityView.h"
namespace View {

    class PacmanView: public EntityView{
    public:
        void update(std::shared_ptr<Logic::Subject> subject) override;
    private:

    };

} // View

#endif //PROJECTPACMAN_PACMANVIEW_H
