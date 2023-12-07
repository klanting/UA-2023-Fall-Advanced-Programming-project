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
        EntityModel(const Vector2D& position, const Vector2D &size, double speed, std::shared_ptr<Move::ModeManager> move_manager);

        virtual void move() override;
        void moveConfirm() override;
        void addObserver(std::shared_ptr<Observer> observer);
        std::pair<bool, std::pair<Vector2D, Vector2D>> collide(std::weak_ptr<Subject> other) override;
        virtual void handleImpassable(std::weak_ptr<Subject> other, bool fix = false) override;

        virtual bool handleDead(std::vector<std::shared_ptr<Subject>> others) override;

        std::shared_ptr<Move::ModeManager> getMoveManager();

        virtual bool isConsumable();
        virtual void changeMode();

        const Vector2D &getPosition() const;
        const Vector2D &getSize() const;
        Vector2D getDirection() const;

        void consume(std::weak_ptr<Subject> other);

        bool isUp() const;
        bool isDown() const;
        bool isLeft() const;
        bool isRight() const;
        virtual ~EntityModel() override;
    protected:

        Vector2D last_position;
        Vector2D position;
        Vector2D size;
        double speed;
        bool consumable = false;

        std::shared_ptr<Move::ModeManager> move_manager;

        std::vector<std::shared_ptr<Observer>> observers;

        std::vector<Vector2D> splitDirection();
        double wait_delay;

    private:
        int getDirectionIndex() const;

    };

} // Logic

#endif //PROJECTPACMAN_ENTITYMODEL_H
