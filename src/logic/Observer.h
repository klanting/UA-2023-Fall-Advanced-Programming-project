//
// Created by tibov on 30/11/23.
//

#ifndef PROJECTPACMAN_OBSERVER_H
#define PROJECTPACMAN_OBSERVER_H
#include <memory>

namespace Logic {
    class Observer {
    public:
        virtual void moved() = 0;
    private:

    };

} // Logic

#endif //PROJECTPACMAN_OBSERVER_H
