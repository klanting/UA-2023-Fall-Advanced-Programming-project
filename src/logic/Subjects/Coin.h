
#ifndef PROJECTPACMAN_COIN_H
#define PROJECTPACMAN_COIN_H
#include "Collectable.h"
namespace Logic {

    class Coin: public Collectable{
    public:
        Coin(const Vector2D<>& position, const std::shared_ptr<Move::ModeManager>& move_manager);
        ~Coin() override = default;
    private:

    };

} // Logic

#endif //PROJECTPACMAN_COIN_H
