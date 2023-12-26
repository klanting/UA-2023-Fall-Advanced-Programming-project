
#ifndef PROJECTPACMAN_COLLECTABLE_H
#define PROJECTPACMAN_COLLECTABLE_H
#include "EntityModel.h"
namespace Logic {

    class Collectable: public EntityModel{
    public:
        /**
         * Constructor for Collectable
         * */
        Collectable(const Vector2D<>& position, const Vector2D<>& size, const std::shared_ptr<Move::ModeManager>& move_manager);

        /**
         * Destructor for Collectable
         * */
        ~Collectable() override = default;

        /**
         * overrides the handleDead function form SuperClass EntityModel
         * This will make sure the handleDead will return true, indication it is allowed to be removed
         * */
        bool handleDead(const std::vector<std::shared_ptr<EntityModel>>& others) override;
    private:

    };

} // Logic

#endif //PROJECTPACMAN_COLLECTABLE_H
