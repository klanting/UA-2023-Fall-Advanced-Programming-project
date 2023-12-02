//
// Created by tibov on 30/11/23.
//

#ifndef PROJECTPACMAN_ABSTRACTFACTORY_H
#define PROJECTPACMAN_ABSTRACTFACTORY_H
#include "Subjects/Subject.h"
#include "Vector2D.h"
#include "Controller/Controller.h"
namespace Logic {

    class AbstractFactory {
    public:
        virtual std::shared_ptr<Subject> createCoin(const Vector2D& position) = 0;
        virtual std::shared_ptr<Subject> createFruit(const Vector2D& position) = 0;
        virtual std::shared_ptr<Subject> createGhost(const Vector2D& position) = 0;
        virtual std::shared_ptr<Subject> createPacman(const Vector2D& position) = 0;
        virtual std::shared_ptr<Subject> createWall(const Vector2D& position) = 0;
    private:
    };

} // Logic

#endif //PROJECTPACMAN_ABSTRACTFACTORY_H
