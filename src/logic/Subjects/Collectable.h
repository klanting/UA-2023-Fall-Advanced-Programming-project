//
// Created by tibov on 25/11/23.
//

#ifndef PROJECTPACMAN_COLLECTABLE_H
#define PROJECTPACMAN_COLLECTABLE_H
#include "EntityModel.h"
namespace Logic {

    class Collectable: public EntityModel{
    public:
        Collectable(const Vector2D& position, std::shared_ptr<Move::ModeManager> move_manager);
    private:

    };

} // Logic

#endif //PROJECTPACMAN_COLLECTABLE_H
