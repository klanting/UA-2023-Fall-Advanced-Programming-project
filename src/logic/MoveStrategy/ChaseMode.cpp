//
// Created by tibov on 25/11/23.
//

#include "ChaseMode.h"
#include "../Random.h"
#include <algorithm>
namespace Logic {
    namespace Move {
        Vector2D ChaseMode::getDirection(Vector2D &to_pacman, const std::vector<Vector2D> &options) const {
            std::shared_ptr<Random> r = Random::getInstance();
            double choice_value = r->getRandom();


            if (choice_value < 0.5){
                //this choice will choose a random option
                return takeRandom(options);
            }else{
                return findClosest(to_pacman, options);
            }


        }

        Vector2D ChaseMode::findClosest(Vector2D &to_pacman, const std::vector<Vector2D> &options) const {

            Vector2D best_direction(0, 0);
            double best_angle = std::numeric_limits<double>::max();
            std::for_each(options.begin(), options.end(),
                          [&best_angle, &to_pacman, &best_direction](Vector2D o){
                    double a = o.getAngle(to_pacman);
                    if (a < best_angle){
                        best_angle = a;
                        best_direction = o;
                    }
                }
            );

            return best_direction;
        }

        Vector2D ChaseMode::takeRandom(const std::vector<Vector2D> &options) const{
            std::shared_ptr<Random> r = Random::getInstance();
            return options[r->getRandomIndex(0, options.size()-1)];
        }
    } // Move
} //Logic