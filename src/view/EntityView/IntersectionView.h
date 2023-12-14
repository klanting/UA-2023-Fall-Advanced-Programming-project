//
// Created by tibov on 14/12/23.
//

#ifndef PROJECTPACMAN_INTERSECTIONVIEW_H
#define PROJECTPACMAN_INTERSECTIONVIEW_H
#include "EntityView.h"
namespace View {

    class IntersectionView: public EntityView{
    public:
        IntersectionView(std::weak_ptr<Logic::EntityModel> entity);
        void moved() override;
    private:
        int getTop() override;
    };

} // View

#endif //PROJECTPACMAN_INTERSECTIONVIEW_H
