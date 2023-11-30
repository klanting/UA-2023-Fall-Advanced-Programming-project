//
// Created by tibov on 30/11/23.
//

#include "EntityView.h"

namespace View {
    EntityView::EntityView(std::weak_ptr<Logic::EntityModel> entity): entity{entity} {

    }
} // View