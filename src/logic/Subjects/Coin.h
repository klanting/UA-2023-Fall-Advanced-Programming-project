
#ifndef PROJECTPACMAN_COIN_H
#define PROJECTPACMAN_COIN_H
#include "Collectable.h"
namespace Logic {

    class Coin: public Collectable{
    public:
        /**
         * Constructor for coin
         * */
        Coin(const Vector2D<>& position, const std::shared_ptr<Move::ModeManager>& move_manager);

        /**
         * Destructor for coin
         * */
        ~Coin() override = default;
    private:

    };

} // Logic

#endif //PROJECTPACMAN_COIN_H
