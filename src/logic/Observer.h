//
// Created by tibov on 30/11/23.
//

#ifndef PROJECTPACMAN_OBSERVER_H
#define PROJECTPACMAN_OBSERVER_H
#include <memory>
#include "Subjects/EntityModel.h"

namespace Logic {
    class Observer {
    public:
        virtual void moved() = 0;
        virtual void consume(std::weak_ptr<EntityModel> other) = 0;
        virtual void died() = 0;
        virtual void finishedLvl() = 0;
    private:

    };

} // Logic

#endif //PROJECTPACMAN_OBSERVER_H
