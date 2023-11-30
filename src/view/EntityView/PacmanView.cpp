//
// Created by tibov on 30/11/23.
//

#include "PacmanView.h"

namespace View {


    void PacmanView::moved() {

    }

    PacmanView::PacmanView(std::weak_ptr<Logic::EntityModel> entity) : EntityView(entity) {

    }
} // View