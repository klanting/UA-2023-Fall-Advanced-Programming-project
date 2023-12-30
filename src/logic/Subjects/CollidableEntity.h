//
// Created by tibov on 30/12/23.
//

#ifndef PROJECTPACMAN_COLLIDABLEENTITY_H
#define PROJECTPACMAN_COLLIDABLEENTITY_H
#include "Subject.h"
namespace Logic {
    /**
     * This class are all the Subjects that can collide with each other,
     * main reason of existence is to split up the EntityModel so they don't gave to check collision
     * To repsect the Single Responsibility Principle
     * */
    class CollidableEntity: public Subject{
    public:

        /**
         * Constructor for CollidableEntity
         * */
        CollidableEntity(const Vector2D<>& position, const Vector2D<> &size);
        ~CollidableEntity() override = default;

        /**
         * returns if this object collides with the other object
         * this returns a std::pair<bool, std::pair<Vector2D<>, Vector2D<>>>
         * the first value of the pair is a boolean that states if the entities collide
         * the first vector2D gives the last position on the path before collision occurs
         * (this position will be the last position for the center of this object)
         * The last Vector will state which Axis we collided, so we can properly handle it in the future
         * */
        [[nodiscard]] std::pair<bool, std::pair<Vector2D<>, Vector2D<>>> collide(const std::weak_ptr<CollidableEntity>& other) const;

        /**
         * This function returns true if we would theoretically collide if we would change the position to the given new position
         * */
        bool collideFuture(const std::weak_ptr<CollidableEntity>& other, const Vector2D<> &new_pos);

        /**
         * Getter for the position of the Entity
         * */
        [[nodiscard]] const Vector2D<> &getPosition() const;

        /**
         * Getter for the size of the Entity
         * */
        [[nodiscard]] const Vector2D<> &getSize() const;



    protected:
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

    };

} // Logic

#endif //PROJECTPACMAN_COLLIDABLEENTITY_H
