

#ifndef PROJECTPACMAN_GHOSTVIEW_H
#define PROJECTPACMAN_GHOSTVIEW_H
#include "EntityView.h"
#include "../../logic/Subjects/Ghost.h"
namespace Logic{
    class Ghost;
}

namespace View {

    class GhostView: public EntityView<Logic::Ghost>{
    public:
        /**
        * Constructor for GhostView
        * */
        GhostView(const std::weak_ptr<Logic::Ghost>& entity, int color_index);
        /**
        * Destructor for GhostView
        * */
        ~GhostView() override = default;
    private:
        int getTop() override;
        /**
         * getLeft will change to show a blue/grey animation when Fear Mode is almost over
         * */
        int getLeft() override;
        int color_index;
    };

} // View

#endif //PROJECTPACMAN_GHOSTVIEW_H
