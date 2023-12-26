//
// Created by tibov on 14/12/23.
//

#ifndef PROJECTPACMAN_INTERSECTIONVIEW_H
#define PROJECTPACMAN_INTERSECTIONVIEW_H
#include "EntityView.h"
#include "../../logic/Subjects/Intersection.h"
namespace View {
    class IntersectionView: public EntityView<Logic::Intersection>{
    public:
        /**
        * Constructor for IntersectionView
        * */
        explicit IntersectionView(const std::weak_ptr<Logic::Intersection>& entity);

        /**
        * Destructor for IntersectionView
        * */
        ~IntersectionView() override = default;
        void moved() override;
    private:
        int getTop() override;
    };

} // View

#endif //PROJECTPACMAN_INTERSECTIONVIEW_H
