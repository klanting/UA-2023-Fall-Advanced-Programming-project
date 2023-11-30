//
// Created by tibov on 30/11/23.
//

#ifndef PROJECTPACMAN_FRUITVIEW_H
#define PROJECTPACMAN_FRUITVIEW_H
#include "EntityView.h"
namespace View {

    class FruitView: public EntityView{
    public:
        FruitView(std::weak_ptr<Logic::EntityModel> entity);
        void moved() override;
    private:

    };

} // View

#endif //PROJECTPACMAN_FRUITVIEW_H
