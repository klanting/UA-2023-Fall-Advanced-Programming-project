//
// Created by tibov on 30/11/23.
//

#ifndef PROJECTPACMAN_OBSERVER_H
#define PROJECTPACMAN_OBSERVER_H
#include <memory>
#include "Subjects/EntityModel.h"

namespace Logic {
    /**
     * Design pattern: Observer
     * This class is an interface class
     * We will observe Entities
     * */
    class Observer {
    public:
        /**
         * observes a move
         * */
        virtual void moved() = 0;

        /**
         * observes if the entity consumes another entity
         * */
        virtual void consume(std::weak_ptr<EntityModel> other) = 0;

        /**
         * observes if an entity dies
         * */
        virtual void died() = 0;

        virtual void finishedLvl() = 0;

        virtual ~Observer() = default;
    private:

    };

} // Logic

#endif //PROJECTPACMAN_OBSERVER_H
