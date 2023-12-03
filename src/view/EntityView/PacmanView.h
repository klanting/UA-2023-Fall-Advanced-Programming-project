//
// Created by tibov on 30/11/23.
//

#ifndef PROJECTPACMAN_PACMANVIEW_H
#define PROJECTPACMAN_PACMANVIEW_H
#include "EntityView.h"
namespace View {

    class PacmanView: public EntityView{
    public:
        PacmanView(std::weak_ptr<Logic::EntityModel> entity);
    private:
        int getTop() override;
        int pacman_row;

    };

} // View

#endif //PROJECTPACMAN_PACMANVIEW_H
