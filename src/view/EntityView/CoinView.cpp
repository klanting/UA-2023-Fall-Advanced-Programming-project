
#include "CoinView.h"
namespace View {

    CoinView::CoinView(const std::weak_ptr<Logic::Coin>& entity) : EntityView(entity) {
        texture.loadFromFile("sprites/Sprites.png", sf::IntRect(400+10, 452+10, 40, 600));

        pixel_width = 20;
        pixel_height = 20;

    }

    int CoinView::getTop() {
        return 0;
    }
} // View

