
#include "EntityModel.h"
#include "../Observer.h"
#include <cmath>
#include <utility>
#include <vector>
namespace Logic {


    EntityModel::EntityModel(const Vector2D<> &position, const Vector2D<> &size, double speed, std::shared_ptr<Move::ModeManager> move_manager): CollidableEntity{position, size}, start_position{position}, speed{speed}{
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





    std::shared_ptr<Move::ModeManager> EntityModel::getMoveManager() const{
        return move_manager;
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