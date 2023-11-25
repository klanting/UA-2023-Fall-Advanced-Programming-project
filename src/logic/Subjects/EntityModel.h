//
// Created by tibov on 25/11/23.
//

#ifndef PROJECTPACMAN_ENTITYMODEL_H
#define PROJECTPACMAN_ENTITYMODEL_H
#include "Subject.h"
namespace Logic {

    class EntityModel: public Subject{
    public:
        EntityModel(const Vector2D& position);
        EntityModel(const Vector2D& position, std::unique_ptr<Move::Mode> mode);

        void move();
    private:

    };

} // Logic

#endif //PROJECTPACMAN_ENTITYMODEL_H
