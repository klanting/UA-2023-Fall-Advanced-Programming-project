//
// Created by tibov on 25/11/23.
//

#ifndef PROJECTPACMAN_COLLECTABLE_H
#define PROJECTPACMAN_COLLECTABLE_H
#include "EntityModel.h"
namespace Logic {

    class Collectable: public EntityModel{
    public:
        Collectable(const Vector2D& position, const Vector2D& size, std::shared_ptr<Move::ModeManager> move_manager);
        virtual ~Collectable() override;
        virtual bool handleDead(std::vector<std::shared_ptr<Subject>> others) override;
    private:

    };

} // Logic

#endif //PROJECTPACMAN_COLLECTABLE_H
