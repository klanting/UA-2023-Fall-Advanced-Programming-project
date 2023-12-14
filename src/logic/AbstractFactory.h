//
// Created by tibov on 30/11/23.
//

#ifndef PROJECTPACMAN_ABSTRACTFACTORY_H
#define PROJECTPACMAN_ABSTRACTFACTORY_H
#include "Subjects/EntityModel.h"
#include "Vector2D.h"
#include "Controller/Controller.h"
#include "Score.h"
namespace Logic {

    class AbstractFactory {
    public:
        virtual std::shared_ptr<EntityModel> createCoin(const Vector2D& position) = 0;
        virtual std::shared_ptr<EntityModel> createFruit(const Vector2D& position) = 0;
        virtual std::shared_ptr<EntityModel> createGhost(const Vector2D& position, double wait_delay, int color_index, double difficulty) = 0;
        virtual std::shared_ptr<EntityModel> createPacman(const Vector2D& position, std::shared_ptr<Score> score) = 0;
        virtual std::shared_ptr<EntityModel> createWall(const Vector2D& position, const Vector2D &size) = 0;
        virtual std::shared_ptr<EntityModel> createIntersection(const Vector2D& position, const Vector2D &size) = 0;
    private:
    };

} // Logic

#endif //PROJECTPACMAN_ABSTRACTFACTORY_H
