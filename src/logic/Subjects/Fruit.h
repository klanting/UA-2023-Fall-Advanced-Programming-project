//
// Created by tibov on 25/11/23.
//

#ifndef PROJECTPACMAN_FRUIT_H
#define PROJECTPACMAN_FRUIT_H
#include "Collectable.h"
namespace Logic {

    class Fruit: public Collectable{
    public:
        Fruit(const Vector2D& position, std::shared_ptr<Move::ModeManager> move_manager);
        bool handleDead(std::vector<std::shared_ptr<EntityModel>> others) override;
    private:
    };

} // Logic

#endif //PROJECTPACMAN_FRUIT_H
