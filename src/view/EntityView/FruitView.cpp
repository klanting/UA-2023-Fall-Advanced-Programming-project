//
// Created by tibov on 30/11/23.
//

#include "FruitView.h"

namespace View {


    void FruitView::moved() {

    }

    FruitView::FruitView(std::weak_ptr<Logic::EntityModel> entity) : EntityView(entity) {

    }
} // View