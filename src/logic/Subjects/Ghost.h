//
// Created by tibov on 25/11/23.
//

#ifndef PROJECTPACMAN_GHOST_H
#define PROJECTPACMAN_GHOST_H
#include "EntityModel.h"
namespace Logic {
    class Ghost: public EntityModel{
    public:
        Ghost(const Vector2D<>& position, double wait_delay, std::shared_ptr<Move::ModeManager> move_manager, double difficulty);
        bool isConsumable() override;
        void changeMode(bool fear) override;
        bool handleDead(std::vector<std::shared_ptr<EntityModel>> others) override;
        void goStartPosition() override;
        void move() override;
        bool AlmostChase() const;
        int bonus() const override;
    private:
        double fear_time;
        double total_fear_time;
    };

} // Logic

#endif //PROJECTPACMAN_GHOSTVIEW_H
