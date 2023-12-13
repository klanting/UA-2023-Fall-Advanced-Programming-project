//
// Created by tibov on 30/11/23.
//

#ifndef PROJECTPACMAN_CONCRETEFACTORY_H
#define PROJECTPACMAN_CONCRETEFACTORY_H
#include "../logic/AbstractFactory.h"
#include "../logic/Subjects/Subject.h"
#include "../logic/Score.h"
using namespace Logic;
namespace View {

    class ConcreteFactory: public Logic::AbstractFactory{
    public:
        std::shared_ptr<EntityModel> createCoin(const Vector2D& position) override;
        std::shared_ptr<EntityModel> createFruit(const Vector2D& position) override;
        std::shared_ptr<EntityModel> createGhost(const Vector2D& position, double wait_delay, int color_index, double difficulty) override;
        std::shared_ptr<EntityModel> createPacman(const Vector2D& position, std::shared_ptr<Score> score) override;
        std::shared_ptr<EntityModel> createWall(const Vector2D& position, const Vector2D &size) override;
    private:
    };

} // View

#endif //PROJECTPACMAN_CONCRETEFACTORY_H
