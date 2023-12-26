//
// Created by tibov on 25/11/23.
//

#ifndef PROJECTPACMAN_PACMAN_H
#define PROJECTPACMAN_PACMAN_H
#include "EntityModel.h"
namespace Logic {

    class Pacman: public EntityModel{
    public:
        /**
         * Constructor for pacman
         * */
        Pacman(const Vector2D<>& position, const std::shared_ptr<Move::ModeManager>& move_manager);

        /**
         * Destructor for pacman
         * */
        ~Pacman() override = default;

        /**
         * On Dead of Pacman bring all the Entities back to their start positions
         * */
        bool handleDead(const std::vector<std::shared_ptr<EntityModel>>& others) override;

    private:

    };

} // Logic

#endif //PROJECTPACMAN_PACMAN_H
