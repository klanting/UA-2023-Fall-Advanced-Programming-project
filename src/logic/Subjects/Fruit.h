//
// Created by tibov on 25/11/23.
//

#ifndef PROJECTPACMAN_FRUIT_H
#define PROJECTPACMAN_FRUIT_H
#include "Collectable.h"
namespace Logic {

    class Fruit: public Collectable{
    public:
        Fruit(const Vector2D& position);
    private:
    };

} // Logic

#endif //PROJECTPACMAN_FRUIT_H
