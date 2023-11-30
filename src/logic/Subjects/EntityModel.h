//
// Created by tibov on 25/11/23.
//

#ifndef PROJECTPACMAN_ENTITYMODEL_H
#define PROJECTPACMAN_ENTITYMODEL_H
#include "Subject.h"
#include "../Stopwatch.h"
namespace Logic {
    class Observer;
    class EntityModel: public Subject{
    public:
        EntityModel(const Vector2D& position, double speed);
        EntityModel(const Vector2D& position, double speed, std::unique_ptr<Move::Mode> mode);

        void move();
        virtual void calculateDirection(const Vector2D& to_pacman, const std::vector<Vector2D>& options);
        void addObserver(std::shared_ptr<Observer> observer);
    protected:
        double speed;
        std::vector<std::shared_ptr<Observer>> observers;

    };

} // Logic

#endif //PROJECTPACMAN_ENTITYMODEL_H
