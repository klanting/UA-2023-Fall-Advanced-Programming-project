//
// Created by tibov on 30/11/23.
//

#include "ConcreteFactory.h"
#include "../logic/Subjects/Coin.h"
#include "../logic/Subjects/Fruit.h"
#include "../logic/Subjects/Ghost.h"
#include "../logic/Subjects/Pacman.h"
#include "../logic/Subjects/Wall.h"

#include "EntityView/CoinView.h"
#include "EntityView/FruitView.h"
#include "EntityView/GhostView.h"
#include "EntityView/PacmanView.h"
#include "EntityView/WallView.h"

namespace View {
    std::shared_ptr<Subject> ConcreteFactory::createCoin(const Vector2D& position) {
        std::shared_ptr<Logic::EntityModel> c = std::make_shared<Logic::Coin>(position);
        c->addObserver(std::make_shared<CoinView>(c));
        return c;
    }

    std::shared_ptr<Subject> ConcreteFactory::createFruit(const Vector2D &position) {
        std::shared_ptr<Logic::EntityModel> c = std::make_shared<Logic::Fruit>(position);
        c->addObserver(std::make_shared<FruitView>(c));
        return c;
    }

    std::shared_ptr<Subject> ConcreteFactory::createGhost(const Vector2D &position) {
        std::shared_ptr<Logic::EntityModel> c = std::make_shared<Logic::Ghost>(position);
        c->addObserver(std::make_shared<GhostView>(c));
        return c;
    }

    std::shared_ptr<Subject> ConcreteFactory::createPacman(const Vector2D &position) {
        std::shared_ptr<Logic::EntityModel> c = std::make_shared<Logic::Pacman>(position);
        c->addObserver(std::make_shared<PacmanView>(c));
        return c;
    }


    std::shared_ptr<Subject> ConcreteFactory::createWall(const Vector2D &position) {
        std::shared_ptr<Logic::EntityModel> c = std::make_shared<Logic::Wall>(position);
        c->addObserver(std::make_shared<WallView>(c));
        return c;
    }
} // View