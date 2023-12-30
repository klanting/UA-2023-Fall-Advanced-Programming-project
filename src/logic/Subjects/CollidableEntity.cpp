//
// Created by tibov on 30/12/23.
//

#include "CollidableEntity.h"

namespace Logic {
    CollidableEntity::CollidableEntity(const Vector2D<> &position, const Vector2D<> &size): position{position}, last_position{position}, size{size} {

    }

    bool CollidableEntity::collideFuture(const std::weak_ptr<CollidableEntity>& other, const Vector2D<> &new_pos){
        //For collide Future we will supposedly move to this position and then verify if this would cause a collision
        Vector2D temp = last_position;
        last_position = position;
        position = new_pos;
        bool hit = collide(other).first;

        position = last_position;
        last_position = temp;

        return hit;
    }

    std::pair<bool, std::pair<Vector2D<>, Vector2D<>>> CollidableEntity::collide(const std::weak_ptr<CollidableEntity>& other) const{
        //check if this entity collides the other entity
        //collision detection will use Continuous Collision Detection
        //this will prevent the Tunneling Event
        //It works by storing its current position and its last position before it moved to this position
        //If the line between those 2 positions intersect with a line of the borders of the other Entity it means we went
        //through a line meaning we have collision

        //throws exception if the weak ptr doesn't exist anymore
        if (other.expired()){
            throw std::bad_weak_ptr{};
        }

        auto other_lock = other.lock();

        //for making the calculating more regular we will take the center positions on the Entities
        Vector2D center_this_last = last_position + size*0.5;
        Vector2D center_this = position + size*0.5;

        Vector2D center_other = other_lock->getPosition() + other_lock->getSize()*0.5;

        //calculate the Vector whose length is the distance it travelled in its last move
        Vector2D distance = (center_this_last-center_this);

        bool collided = false;

        double best = -1;
        int best_index = -1;
        for (int i = 0; i < 2; i++){
            //this booleans guarantee that if we intersect a line that the intersection is on the other object itself and not
            // parallel next to it
            bool old_between = (center_other- other_lock->getSize()*0.5)[(i+1)%2] <= (center_this_last+ size*0.5)[(i+1)%2] && (center_other + other_lock->getSize()*0.5)[(i+1)%2] >= (center_this_last- size*0.5)[(i+1)%2];
            bool new_between = (center_other- other_lock->getSize()*0.5)[(i+1)%2] <= (center_this+ size*0.5)[(i+1)%2] && (center_other + other_lock->getSize()*0.5)[(i+1)%2] >= (center_this- size*0.5)[(i+1)%2];

            if (!(old_between || new_between)){
                continue;
            }

            //depending on which side we come from we have to change the check
            //we can cross line X with point X0 to X1 or X1 to X0
            Vector2D<> change;
            if (distance[i] > 0){
                change = size*0.5;
            }else{
                change = size*(-0.5);
            }

            Vector2D t1 = (center_other - (other_lock->getSize()*0.5) + change - center_this)/distance;
            Vector2D t2 = (center_other + (other_lock->getSize()*0.5) + change - center_this)/distance;

            //store the best value
            //best will be the highest value between 0 and 1
            //we can later use this best for linear interpolation between position and last position
            for (auto t: {t1, t2}){
                if (t[i] > 0 && t[i] <= 1 && t[i] > best){
                    best = t[i];
                    best_index = i;
                }
            }

        }

        //if best is within the asked constraint we will have collision
        if (best > 0 && best <= 1){
            collided = true;
        }

        //in case we have collision we will need to handle that collision
        //based on the data we have we can easily calculate the point just before we collided and which AXIS we collided
        Vector2D<> to_collision = (center_this_last*best)+center_this*(1-best);
        Vector2D<> bounce_direction = Vector2D<>{0, 0};
        if (best_index == 0){
            bounce_direction = Vector2D<>{1, 0};
        }else{
            bounce_direction = Vector2D<>{0, 1};
        }

        return std::make_pair(collided, std::make_pair(to_collision, bounce_direction));

    }

    const Vector2D<> &CollidableEntity::getPosition() const {
        return position;
    }

    const Vector2D<> &CollidableEntity::getSize() const {
        return size;
    }

} // Logic