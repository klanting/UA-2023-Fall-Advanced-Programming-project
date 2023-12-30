//
// Created by tibov on 27/12/23.
//

#ifndef PROJECTPACMAN_WORLDREADERWRD_H
#define PROJECTPACMAN_WORLDREADERWRD_H
#include "WorldReader.h"

    namespace Logic::WorldLoading {

        /**
         * Part of Design pattern: Abstract Factory
         * This class will read self invented .wrd file formats
         * */
        class WorldReaderWRD: public WorldReader{
        public:
            WorldReaderWRD(std::unique_ptr<AbstractFactory>&& factory, const std::shared_ptr<Score>& score);
            std::unique_ptr<World> load(double difficulty, int lives) override;
        private:

        };

    } // WorldLoading
// Logic

#endif //PROJECTPACMAN_WORLDREADERWRD_H
