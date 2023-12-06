//
// Created by tibov on 30/11/23.
//

#ifndef PROJECTPACMAN_CONCRETEFACTORY_H
#define PROJECTPACMAN_CONCRETEFACTORY_H
#include "../logic/AbstractFactory.h"
#include "../logic/Subjects/Subject.h"

using namespace Logic;
namespace View {

    class ConcreteFactory: public Logic::AbstractFactory{
    public:
        std::shared_ptr<Subject> createCoin(const Vector2D& position) override;
        std::shared_ptr<Subject> createFruit(const Vector2D& position) override;
        std::shared_ptr<Subject> createGhost(const Vector2D& position) override;
        std::shared_ptr<Subject> createPacman(const Vector2D& position) override;
        std::shared_ptr<Subject> createWall(const Vector2D& position, const Vector2D &size) override;
    private:
    };

} // View

#endif //PROJECTPACMAN_CONCRETEFACTORY_H
