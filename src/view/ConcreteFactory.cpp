//
// Created by tibov on 30/11/23.
//

#include "ConcreteFactory.h"
#include "../logic/Subjects/Coin.h"
#include "../logic/Subjects/Fruit.h"
#include "../logic/Subjects/Ghost.h"
#include "../logic/Subjects/Pacman.h"
#include "../logic/Subjects/Wall.h"
#include "../logic/Subjects/Intersection.h"

#include "EntityView/CoinView.h"
#include "EntityView/FruitView.h"
#include "EntityView/GhostView.h"
#include "EntityView/PacmanView.h"
#include "EntityView/WallView.h"
#include "EntityView/IntersectionView.h"

#include "../logic/MoveStrategy/ControlMode.h"
#include "../logic/MoveStrategy/PassiveMode.h"
#include "../logic/MoveStrategy/ChaseMode.h"
#include "../logic/MoveStrategy/FearMode.h"
#include "../logic/MoveStrategy/ModeManager.h"

#include "../logic/Score.h"

namespace View {
    std::shared_ptr<EntityModel> ConcreteFactory::createCoin(const Vector2D<>& position) {
        std::unique_ptr<Move::Mode> mode = std::make_unique<Move::PassiveMode>();
        std::shared_ptr<Move::ModeManager> move_manager = std::make_shared<Move::ModeManager>(std::move(mode));

        std::shared_ptr<Logic::Coin> c = std::make_shared<Logic::Coin>(position, move_manager);

        c->addObserver(std::make_shared<CoinView>(c));
        return c;
    }

    std::shared_ptr<EntityModel> ConcreteFactory::createFruit(const Vector2D<> &position) {
        std::unique_ptr<Move::Mode> mode = std::make_unique<Move::PassiveMode>();
        std::shared_ptr<Move::ModeManager> move_manager = std::make_shared<Move::ModeManager>(std::move(mode));

        std::shared_ptr<Logic::Fruit> c = std::make_shared<Logic::Fruit>(position, move_manager);
        c->addObserver(std::make_shared<FruitView>(c));
        return c;
    }

    std::shared_ptr<EntityModel> ConcreteFactory::createGhost(const Vector2D<> &position, double wait_delay, int color_index, double difficulty) {
        std::unique_ptr<Move::Mode> mode = std::make_unique<Move::ChaseMode>();
        std::shared_ptr<Move::ModeManager> move_manager = std::make_shared<Move::ModeManager>(std::move(mode));

        std::shared_ptr<Logic::Ghost> c = std::make_shared<Logic::Ghost>(position, wait_delay, move_manager, difficulty);
        c->addObserver(std::make_shared<GhostView>(c, color_index));
        return c;
    }

    std::shared_ptr<EntityModel> ConcreteFactory::createPacman(const Vector2D<> &position, std::shared_ptr<Score> score) {

        std::unique_ptr<Move::Mode> mode = std::make_unique<Move::ControlMode>();
        std::shared_ptr<Move::ModeManager> move_manager = std::make_shared<Move::ModeManager>(std::move(mode));

        std::shared_ptr<Logic::Pacman> c = std::make_shared<Logic::Pacman>(position, move_manager);
        c->addObserver(std::make_shared<PacmanView>(c));
        c->addObserver(score);
        score->addObserved(c);
        return c;
    }


    std::shared_ptr<EntityModel> ConcreteFactory::createWall(const Vector2D<> &position, const Vector2D<> &size) {
        std::unique_ptr<Move::Mode> mode = std::make_unique<Move::PassiveMode>();
        std::shared_ptr<Move::ModeManager> move_manager = std::make_shared<Move::ModeManager>(std::move(mode));

        std::shared_ptr<Logic::Wall> c = std::make_shared<Logic::Wall>(position, size, move_manager);
        c->addObserver(std::make_shared<WallView>(c));
        return c;
    }

    std::shared_ptr<EntityModel> ConcreteFactory::createIntersection(const Vector2D<> &position, const Vector2D<> &size) {
        std::unique_ptr<Move::Mode> mode = std::make_unique<Move::PassiveMode>();
        std::shared_ptr<Move::ModeManager> move_manager = std::make_shared<Move::ModeManager>(std::move(mode));

        std::shared_ptr<Logic::Intersection> c = std::make_shared<Logic::Intersection>(position, size, move_manager);
        c->addObserver(std::make_shared<IntersectionView>(c));
        return c;
    }
} // View