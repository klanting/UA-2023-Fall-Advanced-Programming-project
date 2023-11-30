//
// Created by tibov on 30/11/23.
//

#include "WallView.h"

namespace View {


    void WallView::moved() {

    }

    WallView::WallView(std::weak_ptr<Logic::EntityModel> entity) : EntityView(entity) {

    }
} // View