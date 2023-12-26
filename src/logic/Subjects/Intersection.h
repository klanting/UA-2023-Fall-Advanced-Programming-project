//
// Created by tibov on 14/12/23.
//

#ifndef PROJECTPACMAN_INTERSECTION_H
#define PROJECTPACMAN_INTERSECTION_H
#include "EntityModel.h"
namespace Logic {

    class Intersection: public EntityModel{
    public:
        /**
         * Constructor for Intersection
         * */
        Intersection(const Vector2D<>& position, const Vector2D<> &size, const std::shared_ptr<Move::ModeManager>& move_manager);

        /**
         * Destructor for Intersection
         * */
        ~Intersection() override = default;

    private:

    };

} // Logic

#endif //PROJECTPACMAN_INTERSECTION_H
