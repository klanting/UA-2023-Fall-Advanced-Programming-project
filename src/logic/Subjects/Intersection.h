//
// Created by tibov on 14/12/23.
//

#ifndef PROJECTPACMAN_INTERSECTION_H
#define PROJECTPACMAN_INTERSECTION_H
#include "EntityModel.h"
namespace Logic {

    class Intersection: public EntityModel{
    public:
        Intersection(const Vector2D<>& position, const Vector2D<> &size, const std::shared_ptr<Move::ModeManager>& move_manager);
        void handleInpassable(const std::weak_ptr<EntityModel>& other, bool fix) override;
        ~Intersection() override = default;
    private:

    };

} // Logic

#endif //PROJECTPACMAN_INTERSECTION_H
