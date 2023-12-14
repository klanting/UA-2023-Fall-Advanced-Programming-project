//
// Created by tibov on 14/12/23.
//

#ifndef PROJECTPACMAN_INTERSECTION_H
#define PROJECTPACMAN_INTERSECTION_H
#include "EntityModel.h"
namespace Logic {

    class Intersection: public EntityModel{
    public:
        Intersection(const Vector2D& position, const Vector2D &size, std::shared_ptr<Move::ModeManager> move_manager);
        void handleInpassable(std::weak_ptr<EntityModel> other, bool fix = false) override;
    private:

    };

} // Logic

#endif //PROJECTPACMAN_INTERSECTION_H
