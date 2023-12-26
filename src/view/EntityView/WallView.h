//
// Created by tibov on 30/11/23.
//

#ifndef PROJECTPACMAN_WALLVIEW_H
#define PROJECTPACMAN_WALLVIEW_H
#include "EntityView.h"
#include "../../logic/Subjects/Wall.h"
namespace View {
    class WallView: public EntityView<Logic::Wall>{
    public:
        /**
        * Constructor for WallView
        * */
        explicit WallView(const std::weak_ptr<Logic::Wall>& entity);

        /**
        * Destructor for PacmanView
        * */
        ~WallView() override = default;
        void moved() override;
    private:
        int getTop() override;
    };

} // View

#endif //PROJECTPACMAN_WALLVIEW_H
