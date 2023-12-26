//
// Created by tibov on 25/11/23.
//

#ifndef PROJECTPACMAN_GHOST_H
#define PROJECTPACMAN_GHOST_H
#include "EntityModel.h"
namespace Logic {
    class Ghost: public EntityModel{
    public:
        /**
         * Constructor for Ghost
         * */
        Ghost(const Vector2D<>& position, double wait_delay, const std::shared_ptr<Move::ModeManager>& move_manager, double difficulty);

        /**
         * Destructor for Ghost
         * */
        ~Ghost() override = default;

        /**
         * returns if this Entity is consumable or not
         * This one will be consumable when in fear mode
         * */
        [[nodiscard]] bool isConsumable() const override;

        /**
         * Make sure that when we changeMode we will change if this is consumable
         * And we will change the Movement Mode
         * */
        void changeMode(bool fear) override;

        /**
         * When this Entity dies, make sure it respawns on its original spawn
         * And that is is not in Fear mode anymore
         * */
        bool handleDead(const std::vector<std::shared_ptr<EntityModel>>& others) override;

        /**
         * Adds some small wait time delay to make sure that if all Ghosts respawn simultaneous that they will not 100% overlap
         * */
        void goStartPosition() override;

        /**
         * Takes into account the time it is still in fear mode
         * */
        void move() override;

        /**
         * AlmostChase will be true if their are only 3 seconds in fear mode left
         * This will make sure we are able to make better animations
         * indicating the almost end of this mode
         * */
        [[nodiscard]] bool AlmostChase() const;

        /**
         * Makes sure their is a Bonusscore for cinsuming Ghosts
         * */
        [[nodiscard]] int bonus() const override;

    private:
        /**
         * time still left in fear mode
         * */
        double fear_time;
        /**
         * Total time in fear mode this Ghost will be on fear mode
         * If this value is low, it means fear mode will not be long
         * */
        double total_fear_time;
    };

} // Logic

#endif //PROJECTPACMAN_GHOST_H
