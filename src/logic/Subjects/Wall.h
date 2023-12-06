//
// Created by tibov on 25/11/23.
//

#ifndef PROJECTPACMAN_WALL_H
#define PROJECTPACMAN_WALL_H
#include "EntityModel.h"
namespace Logic {

    class Wall: public EntityModel{
    public:
        Wall(const Vector2D& position, const Vector2D &size, std::shared_ptr<Move::ModeManager> move_manager);
        void handleImpassable(std::weak_ptr<Subject> other, bool fix = false) override;
    private:
    };

} // Logic

#endif //PROJECTPACMAN_WALL_H
