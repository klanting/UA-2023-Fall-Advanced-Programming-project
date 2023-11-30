//
// Created by tibov on 30/11/23.
//

#ifndef PROJECTPACMAN_OBSERVER_H
#define PROJECTPACMAN_OBSERVER_H
#include <memory>
#include "Subjects/Subject.h"
namespace Logic {
    class Observer {
    public:
        virtual void update(std::shared_ptr<Subject> subject) = 0;
    private:

    };

} // Logic

#endif //PROJECTPACMAN_OBSERVER_H
