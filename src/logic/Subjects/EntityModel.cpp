
#include "EntityModel.h"
#include "../Observer.h"
#include <cmath>
#include <utility>
#include <vector>
namespace Logic {


    EntityModel::EntityModel(const Vector2D<> &position, const Vector2D<> &size, double speed, std::shared_ptr<Move::ModeManager> move_manager): position{position}, speed{speed}, size{size},
                                                                                                                                             last_position{position}, start_position{position}{
        //initializes the data members
        EntityModel::move_manager = std::move(move_manager);
        wait_delay = 0;
    }

    void EntityModel::move() {
        //here the move will occur
        //first we will check if there is some Wait delay
        //we subtract the dela time from the stopwatch with the wait delay
        //we either decrease the wait delay or if the wait delay is over we move the remaining time
        std::shared_ptr<Stopwatch> stopwatch = Logic::Stopwatch::getInstance();
        double delta_time = stopwatch->getDeltaTime();
        if (delta_time-wait_delay < 0){
            wait_delay -= delta_time;

        }else{
            //here we will do the move
            delta_time -= wait_delay;
            wait_delay = 0;

            Vector2D direction = move_manager->getDirection();

            last_position = position;

            //this formula will make sure that we go into the direction for a length based on the delta_time and the speed
            position += direction*delta_time*speed;
        }

        //let the observer know this Entity Moved
        for (const std::shared_ptr<Observer>& observer: observers){
            observer->moved();
        }

    }



    const Vector2D<> &EntityModel::getPosition() const {
        return position;
    }

    const Vector2D<> &EntityModel::getSize() const {
        return size;
    }

    std::shared_ptr<Move::ModeManager> EntityModel::getMoveManager() const{
        return move_manager;
    }

    bool EntityModel::collideFuture(const std::weak_ptr<EntityModel>& other, const Vector2D<> &new_pos){
        //For collide Future we will supposedly move to this position and then verify if this would cause a collision
        Vector2D temp = last_position;
        last_position = position;
        position = new_pos;
        bool hit = collide(other).first;

        position = last_position;
        last_position = temp;

        return hit;
    }

    std::pair<bool, std::pair<Vector2D<>, Vector2D<>>> EntityModel::collide(const std::weak_ptr<EntityModel>& other) const{
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

    void EntityModel::handleInpassable(const std::weak_ptr<EntityModel>& other, bool fix) {
        //here we will rerun the collision to check if their is still collision and how to handle this
        auto p = collide(other);

        if (!p.first){
            return;
        }

        //calculate how far we travelled before the collision happened
        Vector2D<> travelled = (position-last_position);
        Vector2D<> travelled_before_collision = (p.second.first-(last_position + size*0.5));

        //set the position back to just before the collision
        position -= (travelled - travelled_before_collision)*1.0001;


        if (fix){
            //in case we want to go to the remaining direction we calculate mini
            //mini is just the direction we go to if we won't go into the direction we just collided
            Vector2D<> mini = std::min(move_manager->getDirection() - p.second.second, move_manager->getDirection()+ p.second.second,
                                       [](const Vector2D<>& a, const Vector2D<>& b) {return a.getLength() < b.getLength();});
            Vector2D<> to_do = mini*(+(travelled-travelled_before_collision));
            //add the compensating distance
            position += to_do;

        }

        //let observers know there was a change in the move position
        for (const std::shared_ptr<Observer>& observer: observers){
            observer->moved();
        }

    }

    bool EntityModel::isConsumable() const{
        return consumable;
    }

    Vector2D<> EntityModel::getDirection() const {
        return move_manager->getDirection();
    }

    bool EntityModel::isUp() const {
        return getDirectionIndex() == 0 || getDirection() == Vector2D<>{0, -1};
    }

    bool EntityModel::isDown() const {
        return getDirectionIndex() == 1 || getDirection() == Vector2D<>{0, 1};

    }

    bool EntityModel::isLeft() const {
        return getDirectionIndex() == 2 || getDirection() == Vector2D<>{-1, 0};

    }

    bool EntityModel::isRight() const {
        return getDirectionIndex() == 3 || getDirection() == Vector2D<>{1, 0};

    }

    void EntityModel::changeMode(bool fear) {

    }



    bool EntityModel::handleDead(const std::vector<std::shared_ptr<EntityModel>>& others) {
        //in case of dead, let observers know it died
        for (const std::shared_ptr<Observer>& observer: observers){
            observer->died();
        }
        return false;
    }

    int EntityModel::getDirectionIndex() const{
        //this is a private function to calculate which direction the Entity went
        //Because of collision handling the direction it went is not guaranteed the direction it was planning
        //to go to
        //returns the most promising direction it went to
        //0: UP
        //1: Down
        //2: Left
        //3: Right
        Vector2D change = position-last_position;
        if (change.getLength() <= 0.000001){
            return  -1;
        }

        double smallest_angle = std::numeric_limits<double>::max();
        int best_index = -1;

        std::vector<Vector2D<>> directions = {Vector2D<>{0, -1}, Vector2D<>{0, 1}, Vector2D<>{-1, 0}, Vector2D<>{1, 0}};

        for (int i =0; i<directions.size(); i++){
            auto v = directions[i];
            if (v.getAngle(change) < smallest_angle && v.getAngle(move_manager->getDirection()) <= M_PI/3){
                smallest_angle = v.getAngle(change);
                best_index = i;
            }

        }
        return best_index;
    }

    void EntityModel::consume(const std::weak_ptr<EntityModel>& other) {
        //let observers know this entity died
        for (const std::shared_ptr<Observer>& observer: observers){
            observer->consume(other);
        }
    }

    void EntityModel::goStartPosition() {
        //sets entity back to start position
        last_position = start_position;
        position = start_position;

    }

    int EntityModel::bonus() const{
        return 0;
    }


} // Logic