
#ifndef PROJECTPACMAN_MODEMANAGER_H
#define PROJECTPACMAN_MODEMANAGER_H
#include "Mode.h"
#include "memory"

    namespace Logic::Move {

        /**
         * This class can be seen as a Strategy Manager
         * Each Strategy referred to as Mode decides the behaviour of an entity with regards of deciding a direction
         * */
        class ModeManager {
        public:
            explicit ModeManager(std::unique_ptr<Mode> mode);

            void makeDirection(const Vector2D<>& to_pacman, const std::vector<Vector2D<>>& options) const;
            Vector2D<> getDirection();

            void setStrategy(std::unique_ptr<Mode> mode);

        private:
            std::unique_ptr<Mode> strategy;
        };

    } // Move
//Logic

#endif //PROJECTPACMAN_MODEMANAGER_H
