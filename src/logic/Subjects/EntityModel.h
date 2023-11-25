//
// Created by tibov on 25/11/23.
//

#ifndef PROJECTPACMAN_ENTITYMODEL_H
#define PROJECTPACMAN_ENTITYMODEL_H
#include "Subject.h"
#include "../Stopwatch.h"
namespace Logic {

    class EntityModel: public Subject{
    public:
        EntityModel(const Vector2D& position, double speed);
        EntityModel(const Vector2D& position, double speed, std::unique_ptr<Move::Mode> mode);

        void move();
    private:
        double speed;

    };

} // Logic

#endif //PROJECTPACMAN_ENTITYMODEL_H
