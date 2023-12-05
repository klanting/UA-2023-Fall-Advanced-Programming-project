//
// Created by tibov on 25/11/23.
//

#include "EntityModel.h"
#include "../MoveStrategy/PassiveMode.h"
#include "../Observer.h"
#include <iostream>
#include <math.h>
#include <vector>
namespace Logic {
    template <typename T>
    bool between(T a, T b, T c){
        //returns true if c is between a and b
        return a <= c && c <= b;
    }

    EntityModel::EntityModel(const Vector2D &position, const Vector2D &size, double speed, std::shared_ptr<Move::ModeManager> move_manager): position{position}, speed{speed}, size{size},
                                                                                                                                             last_position{position} {
        EntityModel::move_manager = move_manager;
    }

    void EntityModel::move() {
        //move function

        std::shared_ptr<Stopwatch> stopwatch= Logic::Stopwatch::getInstance();

        Vector2D direction = move_manager->getDirection();

        last_position = position;

        position += direction*stopwatch->getDeltaTime()*speed;



    }


    void EntityModel::addObserver(std::shared_ptr<Observer> observer) {
        observers.push_back(observer);
    }

    const Vector2D &EntityModel::getPosition() const {
        return position;
    }

    const Vector2D &EntityModel::getSize() const {
        return size;
    }

    std::shared_ptr<Move::ModeManager> EntityModel::getMoveManager() {
        return move_manager;
    }

    std::pair<bool, std::pair<Vector2D, Vector2D>> EntityModel::collide(std::weak_ptr<Subject> other) {

        if (other.expired()){
            throw "expired";
        }

        auto other_lock = other.lock();

        Vector2D center_this_last = last_position + size*0.5;
        Vector2D center_this = position + size*0.5;
        Vector2D center_other = other_lock->getPosition() + other_lock->getSize()*0.5;

        Vector2D distance = (center_this_last-center_this);

        bool collided = false;

        double best = std::numeric_limits<double>::infinity();
        int best_index = -1;
        for (int i = 0; i < 2; i++){
            bool old_between = (center_other- other_lock->getSize()*0.5)[(i+1)%2] <= (center_this_last+ size*0.5)[(i+1)%2] && (center_other + other_lock->getSize()*0.5)[(i+1)%2] >= (center_this_last- size*0.5)[(i+1)%2];
            bool new_between = (center_other- other_lock->getSize()*0.5)[(i+1)%2] <= (center_this+ size*0.5)[(i+1)%2] && (center_other + other_lock->getSize()*0.5)[(i+1)%2] >= (center_this- size*0.5)[(i+1)%2];

            if (!(old_between || new_between)){
                continue;
            }

            Vector2D change = {0, 0};
            if (distance[i] > 0){
                change = size*0.5;
            }else{
                change = size*(-0.5);
            }

            Vector2D t1 = (center_other - (other_lock->getSize()*0.5) + change - center_this)/distance;
            Vector2D t2 = (center_other + (other_lock->getSize()*0.5) + change - center_this)/distance;

            for (auto t: {t1, t2}){
                if (t[i] > 0 && t[i] < best){
                    best = t[i];
                    best_index = i;
                }
            }

        }

        if (best < 1){
            collided = true;
        }

        Vector2D to_collision = (center_this_last*best)+center_this*(1-best);
        Vector2D bounce_direction = Vector2D{0, 0};
        if (best_index == 0){
            bounce_direction = Vector2D{1, 0};
        }else{
            bounce_direction = Vector2D{0, 1};
        }

        return std::make_pair(collided, std::make_pair(to_collision, bounce_direction));

        /*
        Vector2D a = position;
        Vector2D b = size + a;

        Vector2D c = other.lock()->getPosition();
        Vector2D d = other.lock()->getSize() + c;

        std::vector<Vector2D> baselines = {Vector2D{1, 0}, Vector2D{0, 1}};
        bool collided = true;
        Vector2D max_overlap = Vector2D{0, 0};
        for (auto& baseline: baselines){
            Vector2D a_c = a.projection(baseline);
            Vector2D b_c = b.projection(baseline);
            Vector2D c_c = c.projection(baseline);
            Vector2D d_c = d.projection(baseline);

            bool local_between = between<Logic::Vector2D>(a_c, b_c, c_c) || between<Logic::Vector2D>(c_c,d_c,a_c);
            if (!local_between){
                collided = false;
                break;
            }

            std::vector<Vector2D> distances = {d_c-a_c, c_c-b_c};

            Vector2D dir = move_manager->getDirection().projection(baseline);

            auto index = std::min_element(distances.begin(), distances.end(), [&dir](const Vector2D& a, const Vector2D& b){return a.getLength() < b.getLength();});
            max_overlap += *index;

        }


        return std::make_pair(collided, max_overlap);
        */
    }

    void EntityModel::handleImpassable(std::weak_ptr<Subject> other, bool fix) {


        auto p = collide(other);

        if (!p.first){
            return;
        }

        Vector2D travelled = (position-last_position);
        Vector2D travelled_before_collision = (p.second.first-(last_position + size*0.5));

        Vector2D mini = std::min(move_manager->getDirection() - p.second.second, move_manager->getDirection()+ p.second.second, [](const Vector2D& a, const Vector2D& b) {return a.getLength() < b.getLength();});

        //Vector2D to_do = mini*(travelled-travelled_before_collision).getLength();
        Vector2D to_do = mini*(+(travelled-travelled_before_collision));
        position -= (travelled - travelled_before_collision)*1.0001;

        if (fix){
            position += to_do;
        }

        other.lock()->debug_green = true;


    }

    bool EntityModel::isConsumable() {
        return consumable;
    }

    Vector2D EntityModel::getDirection() const {
        return move_manager->getDirection();
    }

    bool EntityModel::isUp() const {
        Vector2D change = position-last_position;
        return (abs(change[1]) > abs(change[0]) && change[1] < 0 && move_manager->getDirection().getLength() > 1) || move_manager->getDirection() == Vector2D{0, -1};
        //return Vector2D{0, -1}.getAngle(position-last_position) < M_PI/2.0;
    }

    bool EntityModel::isDown() const {
        Vector2D change = position-last_position;
        return (abs(change[1]) > abs(change[0]) && change[1] > 0 && move_manager->getDirection().getLength() > 1) || move_manager->getDirection() == Vector2D{0, 1};
        //return Vector2D{0, 1}.getAngle(position-last_position) < M_PI/2.0;
    }

    bool EntityModel::isLeft() const {
        Vector2D change = position-last_position;
        return (abs(change[0]) > abs(change[1]) && change[0] < 0 && move_manager->getDirection().getLength() > 1) || move_manager->getDirection() == Vector2D{-1, 0};
        //return Vector2D{-1, 0}.getAngle(position-last_position) < M_PI/2.0;
    }

    bool EntityModel::isRight() const {
        Vector2D change = position-last_position;
        return (abs(change[0]) > abs(change[1]) && change[0] > 0 && move_manager->getDirection().getLength() > 1) || move_manager->getDirection() == Vector2D{1, 0};
        //return Vector2D{1, 0}.getAngle(position-last_position) < M_PI/2.0;
    }

    void EntityModel::changeMode() {

    }

    std::vector<Vector2D> EntityModel::splitDirection() {
        auto v = move_manager->getDirection();
        auto temp = {Vector2D{v[0], 0}, Vector2D{0, v[1]}};
        std::vector<Vector2D> output = {};

        for (auto t: temp){
            if (t == Vector2D{0, 0}){
                continue;
            }
            output.push_back(t);
        }

        return output;
    }

    void EntityModel::handleDead(std::vector<std::shared_ptr<Subject>> others) {

    }

    EntityModel::~EntityModel() {

    }

    void EntityModel::moveConfirm() {
        for (std::shared_ptr<Observer> observer: observers){
            observer->moved();
        }
    }

} // Logic