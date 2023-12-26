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
        /**
        * Constructor for PacmanView
        * */
        explicit PacmanView(const std::weak_ptr<Logic::Pacman>& entity);

        /**
        * Destructor for PacmanView
        * */
        ~PacmanView() override = default;
    private:
        int getTop() override;

    };

} // View

#endif //PROJECTPACMAN_PACMANVIEW_H
