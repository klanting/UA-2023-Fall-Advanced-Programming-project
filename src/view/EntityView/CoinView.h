//
// Created by tibov on 30/11/23.
//

#ifndef PROJECTPACMAN_COINVIEW_H
#define PROJECTPACMAN_COINVIEW_H
#include "EntityView.h"
namespace View {

    class CoinView: public EntityView{
    public:
        CoinView(std::weak_ptr<Logic::EntityModel> entity);
    private:
        int getTop() override;
    };

} // View

#endif //PROJECTPACMAN_COINVIEW_H
