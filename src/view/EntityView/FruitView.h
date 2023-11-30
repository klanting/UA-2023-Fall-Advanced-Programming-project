//
// Created by tibov on 30/11/23.
//

#ifndef PROJECTPACMAN_FRUITVIEW_H
#define PROJECTPACMAN_FRUITVIEW_H
#include "EntityView.h"
namespace View {

    class FruitView: public EntityView{
    public:
        void update(std::shared_ptr<Logic::Subject> subject) override;
    private:

    };

} // View

#endif //PROJECTPACMAN_FRUITVIEW_H
