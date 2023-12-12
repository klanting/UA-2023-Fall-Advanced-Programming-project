//
// Created by tibov on 25/11/23.
//

#include "Fruit.h"

namespace Logic {
    Fruit::Fruit(const Vector2D &position, std::shared_ptr<Move::ModeManager> move_manager) : Collectable(position, Vector2D{0.06,0.06}, move_manager) {

    }

    bool Fruit::handleDead(std::vector<std::shared_ptr<EntityModel>> others) {
        for (auto o: others){
            o->changeMode(true);
        }
        return Collectable::handleDead(others);

    }

    int Fruit::bonus() const {
        return 100;
    }
} // Logic