//
// Created by tibov on 30/11/23.
//

#ifndef PROJECTPACMAN_COINVIEW_H
#define PROJECTPACMAN_COINVIEW_H
#include "EntityView.h"
namespace View {

    class CoinView: public EntityView{
    public:
        void update(std::shared_ptr<Logic::Subject> subject) override;
    private:

    };

} // View

#endif //PROJECTPACMAN_COINVIEW_H
