

#ifndef PROJECTPACMAN_GHOSTVIEW_H
#define PROJECTPACMAN_GHOSTVIEW_H
#include "EntityView.h"
#include "../../logic/Subjects/Ghost.h"
namespace Logic{
    class Ghost;
}

namespace View {
    class GhostView: public EntityView{
    public:
        GhostView(std::weak_ptr<Logic::Ghost> entity, int color_index);
    private:
        int getTop() override;
        int getLeft() override;
        int color_index;
        std::weak_ptr<Logic::Ghost> ghost;
    };

} // View

#endif //PROJECTPACMAN_GHOSTVIEW_H
