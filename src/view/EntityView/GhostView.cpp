//
// Created by tibov on 30/11/23.
//

#include "GhostView.h"

namespace View {


    void GhostView::moved() {

    }

    GhostView::GhostView(std::weak_ptr<Logic::EntityModel> entity) : EntityView(entity) {

    }
} // View