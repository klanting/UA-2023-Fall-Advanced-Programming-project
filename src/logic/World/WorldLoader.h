//
// Created by tibov on 22/12/23.
//

#ifndef PROJECTPACMAN_WORLDLOADER_H
#define PROJECTPACMAN_WORLDLOADER_H
#include <memory>
#include "../Subjects/EntityModel.h"
#include "../AbstractFactory.h"

namespace Logic::WorldLoading {

    struct WorldData{
        std::shared_ptr<EntityModel> pacman;
        std::vector<std::shared_ptr<EntityModel>> entities;
        std::vector<std::shared_ptr<EntityModel>> not_passable;
        std::vector<std::shared_ptr<EntityModel>> intersection;

    };

    class WorldLoader {
    public:
        WorldLoader(const std::shared_ptr<AbstractFactory>& factory);
        virtual WorldData load() = 0;

    protected:
        std::shared_ptr<AbstractFactory> factory;


    };

} // Logic::WorldLoading

#endif //PROJECTPACMAN_WORLDLOADER_H
