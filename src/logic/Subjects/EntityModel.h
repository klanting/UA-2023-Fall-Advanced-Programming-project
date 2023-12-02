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
        EntityModel(const Vector2D& position, double speed, std::shared_ptr<Move::ModeManager> move_manager);

        void move();
        void addObserver(std::shared_ptr<Observer> observer);
        bool collide(std::weak_ptr<Subject> other);

        std::shared_ptr<Move::ModeManager> getMoveManager();

        const Vector2D &getPosition() const;
        const Vector2D &getSize() const;
    protected:
        Vector2D position;
        Vector2D size;
        double speed;

        std::shared_ptr<Move::ModeManager> move_manager;

        std::vector<std::shared_ptr<Observer>> observers;

    };

} // Logic

#endif //PROJECTPACMAN_ENTITYMODEL_H
