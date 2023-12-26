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
        /**
         * Constructor for EntityModel
         * */
        EntityModel(const Vector2D<>& position, const Vector2D<> &size, double speed, std::shared_ptr<Move::ModeManager> move_manager);

        /**
         * Destructor for EntityModel
         * */
        ~EntityModel() override = default;

        /**
         * move function
         * when this function is called, its position will move in the direction provided
         * by the move manager
         * The distance it travels depends on the time between ticks and the speed
         * */
        virtual void move();

        /**
         * returns if this object collides with the other object
         * this returns a std::pair<bool, std::pair<Vector2D<>, Vector2D<>>>
         * the first value of the pair is a boolean that states if the entities collide
         * the first vector2D gives the last position on the path before collision occurs
         * (this position will be the last position for the center of this object)
         * The last Vector will state which Axis we collided, so we can properly handle it in the future
         * */
        [[nodiscard]] std::pair<bool, std::pair<Vector2D<>, Vector2D<>>> collide(const std::weak_ptr<EntityModel>& other) const;

        /**
         * This function returns true if we would theoretically collide if we would change the position to the given new position
         * */
        bool collideFuture(const std::weak_ptr<EntityModel>& other, const Vector2D<> &new_pos);

        /**
         * This handles the situation when we face an immovable object (like a Wall)
         * This also has a fix parameter
         * First we will make sure that the objects don't collide anymore
         * We might be able to go in multiple directions at once, if fix ==true
         * We will still go to the directions not blocked
         * if fix == false
         * we will not continue in the other possible directions
         * */
        virtual void handleInpassable(const std::weak_ptr<EntityModel>& other, bool fix);

        /**
         * This function is called when this entity dies
         * it gets a list of the other Entities so we might be able to do some changes on those too
         * It also returns a bool stating whether or not the entity needs to be removed
         * */
        virtual bool handleDead(const std::vector<std::shared_ptr<EntityModel>>& others);

        /**
         * Getter for the MoveManager
         * */
        [[nodiscard]] std::shared_ptr<Move::ModeManager> getMoveManager() const;

        /**
         * this function returns if an Entity is consumable, this might change
         * In our project Colletables are always consumable, and Ghosts are when in fear mode
         * */
        [[nodiscard]] virtual bool isConsumable() const;

        /**
         * ChangeMode function will be called when a Fruit is collected and we need to change the mode
         * This will in our project only be useful for Ghost, but theoretically we can apply this change for any Entity
         * */
        virtual void changeMode(bool fear);

        /**
         * Getter for the position of the Entity
         * */
        [[nodiscard]] const Vector2D<> &getPosition() const;

        /**
         * Getter for the size of the Entity
         * */
        [[nodiscard]] const Vector2D<> &getSize() const;

        /**
         * Getter for the direction for the direction of the MoveManager
         * This makes it easier to get the direction
         * */
        [[nodiscard]] Vector2D<> getDirection() const;


        /**
         * This function we be called to make clear that this Entity consumes another Entity
         * */
        void consume(const std::weak_ptr<EntityModel>& other);

        /**
         * Getter to see if the lastEntityMovement went Up
         * */
        [[nodiscard]] bool isUp() const;

        /**
         * Getter to see if the lastEntityMovement went Down
         * */
        [[nodiscard]] bool isDown() const;

        /**
         * Getter to see if the lastEntityMovement went Left
         * */
        [[nodiscard]] bool isLeft() const;

        /**
         * Getter to see if the lastEntityMovement went Right
         * */
        [[nodiscard]] bool isRight() const;

        /**
         * Set this Entity to the position it originally started
         * Useful to set Ghost/Pacman to their Original Position
         * */
        virtual void goStartPosition();

        /**
         * Check the bonusValue of this Entity if it would be consumed
         * */
        [[nodiscard]] virtual int bonus() const;


    protected:
        /**
         * Start position of the Entity
         * */
        Vector2D<> start_position;

        /**
         * position of the Entity
         * */
        Vector2D<> position;

        /**
         * position of the Entity before its last move
         * */
        Vector2D<> last_position;

        /**
         * size of the Entity
         * */
        Vector2D<> size;

        /**
         * speed of the Entity
         * */
        double speed;

        /**
         * bool that states if the Entity is consumable
         * */
        bool consumable = false;

        /**
         *ptr to the moveManager
         * */
        std::shared_ptr<Move::ModeManager> move_manager;

        /**
         * Delay that an entity needs to wait before it starts moving
         * */
        double wait_delay;

    private:
        /**
         * get an index that describes which way the Entity was going during its last move
         * */
        [[nodiscard]] int getDirectionIndex() const;

    };

} // Logic

#endif //PROJECTPACMAN_ENTITYMODEL_H
