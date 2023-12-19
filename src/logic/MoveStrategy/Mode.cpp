//
// Created by tibov on 25/11/23.
//

#include "Mode.h"

namespace Logic {
    namespace Move {

        Vector2D Mode::findBest(const Vector2D &to_entity, const std::vector<Vector2D> &options, const std::function<bool(double, double)>& op) const{

            Vector2D best_direction(0, 0);
            double best_angle = 0;

            for (const Vector2D& o: options){
                double a = o.getAngle(to_entity);
                if (op(a, best_angle) || best_direction == Vector2D{0,0}){
                    best_angle = a;
                    best_direction = o;
                }
            }


            return best_direction;
        }

        Vector2D Mode::takeRandom(const std::vector<Vector2D> &options) const{
            std::shared_ptr<Random> r = Random::getInstance();
            return options[r->getRandomIndex(0, options.size()-1)];
        }

        const Vector2D &Mode::getDirection() const {
            return direction;
        }

        Mode::Mode(): direction{Vector2D(0,0)} {

        }

    } // Logic
} // Move