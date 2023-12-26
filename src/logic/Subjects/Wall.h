//
// Created by tibov on 25/11/23.
//

#ifndef PROJECTPACMAN_WALL_H
#define PROJECTPACMAN_WALL_H
#include "EntityModel.h"
namespace Logic {

    class Wall: public EntityModel{
    public:
        /**
         * Constructor for Wall
         * */
        Wall(const Vector2D<>& position, const Vector2D<> &size, const std::shared_ptr<Move::ModeManager>& move_manager);
        /**
         * Destructor for Wall
         * */
        ~Wall() override = default;

        /**
         * Walls themselves are Inpassable, so to prevent collision between walls we will make sure this function
         * Will not handle collision with other walls
         * */
        void handleInpassable(const std::weak_ptr<EntityModel>& other, bool fix) override;

    private:
    };

} // Logic

#endif //PROJECTPACMAN_WALL_H
