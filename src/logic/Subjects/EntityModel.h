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
        EntityModel(const Vector2D<>& position, const Vector2D<> &size, double speed, std::shared_ptr<Move::ModeManager> move_manager);

        virtual void move();

        std::pair<bool, std::pair<Vector2D<>, Vector2D<>>> collide(const std::weak_ptr<EntityModel>& other);
        bool collideFuture(const std::weak_ptr<EntityModel>& other, const Vector2D<> &new_pos);

        virtual void handleInpassable(const std::weak_ptr<EntityModel>& other, bool fix);
        virtual bool handleDead(const std::vector<std::shared_ptr<EntityModel>>& others);

        std::shared_ptr<Move::ModeManager> getMoveManager();

        virtual bool isConsumable();
        virtual void changeMode(bool fear);

        [[nodiscard]] const Vector2D<> &getPosition() const;
        [[nodiscard]] const Vector2D<> &getSize() const;
        [[nodiscard]] Vector2D<> getDirection() const;

        void consume(const std::weak_ptr<EntityModel>& other);

        [[nodiscard]] bool isUp() const;
        [[nodiscard]] bool isDown() const;
        [[nodiscard]] bool isLeft() const;
        [[nodiscard]] bool isRight() const;
        virtual ~EntityModel() override = default;
        virtual void goStartPosition();


        bool debug_green = false;
        [[nodiscard]] virtual int bonus() const;


    protected:
        Vector2D<> start_position;
        Vector2D<> last_position;
        Vector2D<> position;
        Vector2D<> size;
        double speed;
        bool consumable = false;



        std::shared_ptr<Move::ModeManager> move_manager;


        double wait_delay;

    private:
        [[nodiscard]] int getDirectionIndex() const;

    };

} // Logic

#endif //PROJECTPACMAN_ENTITYMODEL_H
