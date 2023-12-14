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
        EntityModel(const Vector2D& position, const Vector2D &size, double speed, std::shared_ptr<Move::ModeManager> move_manager);

        virtual void move();
        std::pair<bool, std::pair<Vector2D, Vector2D>> collide(std::weak_ptr<EntityModel> other);
        bool collideFuture(std::weak_ptr<EntityModel> other, const Vector2D &new_pos);

        virtual void handleInpassable(std::weak_ptr<EntityModel> other, bool fix = false);

        virtual bool handleDead(std::vector<std::shared_ptr<EntityModel>> others);

        std::shared_ptr<Move::ModeManager> getMoveManager();

        virtual bool isConsumable();
        virtual void changeMode(bool fear);

        const Vector2D &getPosition() const;
        const Vector2D &getSize() const;
        Vector2D getDirection() const;
        void persistMovement();

        void consume(std::weak_ptr<EntityModel> other);

        bool isUp() const;
        bool isDown() const;
        bool isLeft() const;
        bool isRight() const;
        virtual ~EntityModel() override;
        virtual void goStartPosition();


        bool debug_green = false;
        virtual int bonus() const;

    protected:
        Vector2D start_position;
        Vector2D last_position;
        Vector2D position;
        Vector2D size;
        double speed;
        bool consumable = false;



        std::shared_ptr<Move::ModeManager> move_manager;


        double wait_delay;

    private:
        int getDirectionIndex() const;

    };

} // Logic

#endif //PROJECTPACMAN_ENTITYMODEL_H
