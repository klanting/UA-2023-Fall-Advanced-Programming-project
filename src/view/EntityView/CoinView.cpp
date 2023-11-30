//
// Created by tibov on 30/11/23.
//

#include "CoinView.h"

namespace View {
    void View::CoinView::moved() {

    }

    CoinView::CoinView(std::weak_ptr<Logic::EntityModel> entity) : EntityView(entity) {

    }
} // View

