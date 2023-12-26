//
// Created by tibov on 30/11/23.
//

#ifndef PROJECTPACMAN_COINVIEW_H
#define PROJECTPACMAN_COINVIEW_H
#include "EntityView.h"
#include "../../logic/Subjects/Coin.h"
namespace View {

    class CoinView: public EntityView<Logic::Coin>{
    public:
        /**
         * Constructor for CoinView
         * */
        explicit CoinView(const std::weak_ptr<Logic::Coin>& entity);

        /**
         * Destructor for CoinView
         * */
        ~CoinView() override = default;
    private:
        int getTop() override;
    };

} // View

#endif //PROJECTPACMAN_COINVIEW_H
