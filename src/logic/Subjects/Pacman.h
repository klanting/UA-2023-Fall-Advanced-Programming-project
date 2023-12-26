//
// Created by tibov on 25/11/23.
//

#ifndef PROJECTPACMAN_PACMAN_H
#define PROJECTPACMAN_PACMAN_H
#include "EntityModel.h"
namespace Logic {

    class Pacman: public EntityModel{
    public:
        Pacman(const Vector2D<>& position, const std::shared_ptr<Move::ModeManager>& move_manager);
        bool handleDead(const std::vector<std::shared_ptr<EntityModel>>& others) override;
        ~Pacman() override = default;
    private:

    };

} // Logic

#endif //PROJECTPACMAN_PACMAN_H
