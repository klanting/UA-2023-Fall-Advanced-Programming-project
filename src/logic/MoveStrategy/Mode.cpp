//
// Created by tibov on 25/11/23.
//

#include "Mode.h"

namespace Logic {
    namespace Move {

        //find best direction based on a given operator
        Vector2D<> Mode::findBest(const Vector2D<> &to_entity, const std::vector<Vector2D<>> &options, const std::function<bool(double, double)>& op) const{
            //initialize the best-direction parameters
            Vector2D<> best_direction(0, 0);
            double best_angle = 0;

            // execute every option to see if the angle is better based on the operation
            for (const Vector2D<>& o: options){
                double a = o.getAngle(to_entity);
                //for minimize the operation will be '<' and for maximize '>'
                if (op(a, best_angle) || best_direction == Vector2D<>{0,0}){
                    //if this direction is better we chance the direction and best_angle
                    best_angle = a;
                    best_direction = o;
                }
            }


            return best_direction;
        }

        //here we will just take a random direction among the possible directions
        Vector2D<> Mode::takeRandom(const std::vector<Vector2D<>> &options) const{
            std::shared_ptr<Random> r = Random::getInstance();
            return options[r->getRandomIndex(0, options.size()-1)];
        }

        const Vector2D<> &Mode::getDirection() const {
            return direction;
        }

        Mode::Mode(): direction{Vector2D<>(0,0)} {

        }

    } // Logic
} // Move