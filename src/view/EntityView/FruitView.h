//
// Created by tibov on 30/11/23.
//

#ifndef PROJECTPACMAN_FRUITVIEW_H
#define PROJECTPACMAN_FRUITVIEW_H
#include "EntityView.h"
#include "../../logic/Subjects/Fruit.h"
namespace View {

    class FruitView: public EntityView<Logic::Fruit>{
    public:
        FruitView(std::weak_ptr<Logic::Fruit> entity);

    private:
        int getTop() override;
    };

} // View

#endif //PROJECTPACMAN_FRUITVIEW_H
