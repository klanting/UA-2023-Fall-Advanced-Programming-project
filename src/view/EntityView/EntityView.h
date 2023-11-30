//
// Created by tibov on 30/11/23.
//

#ifndef PROJECTPACMAN_ENTITYVIEW_H
#define PROJECTPACMAN_ENTITYVIEW_H
#include "../../logic/Observer.h"
#include "../../logic/Subjects/EntityModel.h"
namespace View {

    class EntityView: public Logic::Observer{
    public:
        EntityView(std::weak_ptr<Logic::EntityModel> entity);
        virtual void moved() = 0;
    protected:
        std::weak_ptr<Logic::EntityModel> entity;
    private:
    };

} // View

#endif //PROJECTPACMAN_ENTITYVIEW_H
