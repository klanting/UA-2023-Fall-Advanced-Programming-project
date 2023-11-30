//
// Created by tibov on 30/11/23.
//

#ifndef PROJECTPACMAN_ENTITYVIEW_H
#define PROJECTPACMAN_ENTITYVIEW_H
#include "../../logic/Observer.h"
namespace View {

class EntityView: public Logic::Observer{
    public:
    virtual void update(std::shared_ptr<Logic::Subject> subject) = 0;
    private:
    };

} // View

#endif //PROJECTPACMAN_ENTITYVIEW_H
