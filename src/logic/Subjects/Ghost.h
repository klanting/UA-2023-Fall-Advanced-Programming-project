//
// Created by tibov on 25/11/23.
//

#ifndef PROJECTPACMAN_GHOSTVIEW_H
#define PROJECTPACMAN_GHOST_H
#include "EntityModel.h"
namespace Logic {

    class Ghost: public EntityModel{
    public:
        Ghost(const Vector2D& position);
    private:
    };

} // Logic

#endif //PROJECTPACMAN_GHOSTVIEW_H
