//
// Created by tibov on 25/11/23.
//

#ifndef PROJECTPACMAN_GHOST_H
#define PROJECTPACMAN_GHOST_H
#include "EntityModel.h"
namespace Logic {
    class Ghost: public EntityModel{
    public:
        Ghost(const Vector2D<>& position, double wait_delay, const std::shared_ptr<Move::ModeManager>& move_manager, double difficulty);
        bool isConsumable() const override;
        void changeMode(bool fear) override;
        bool handleDead(const std::vector<std::shared_ptr<EntityModel>>& others) override;
        void goStartPosition() override;
        void move() override;
        [[nodiscard]] bool AlmostChase() const;
        [[nodiscard]] int bonus() const override;
        ~Ghost() override = default;
    private:
        double fear_time;
        double total_fear_time;
    };

} // Logic

#endif //PROJECTPACMAN_GHOST_H
