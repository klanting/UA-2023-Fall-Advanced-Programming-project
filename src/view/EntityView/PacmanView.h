//
// Created by tibov on 30/11/23.
//

#ifndef PROJECTPACMAN_PACMANVIEW_H
#define PROJECTPACMAN_PACMANVIEW_H
#include "EntityView.h"
#include "../../logic/Subjects/Pacman.h"
namespace View {

    class PacmanView: public EntityView<Logic::Pacman>{
    public:
        PacmanView(std::weak_ptr<Logic::Pacman> entity);
    private:
        int getTop() override;
        int pacman_row;

    };

} // View

#endif //PROJECTPACMAN_PACMANVIEW_H
