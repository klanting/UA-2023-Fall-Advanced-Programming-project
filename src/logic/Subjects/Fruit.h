//
// Created by tibov on 25/11/23.
//

#ifndef PROJECTPACMAN_FRUIT_H
#define PROJECTPACMAN_FRUIT_H
#include "Collectable.h"
namespace Logic {

    class Fruit: public Collectable{
    public:
        /**
         * Constructor for Fruit
         * */
        Fruit(const Vector2D<>& position, std::shared_ptr<Move::ModeManager> move_manager);

        /**
         * Destructor for Fruit
         * */
        ~Fruit() override = default;

        /**
         * Overrides handleDead from superclass Collectable
         * This will make sure if a Fruit Entity dies all other entities will change mode with fear mode bool true
         * */
        bool handleDead(const std::vector<std::shared_ptr<EntityModel>>& others) override;
        [[nodiscard]] int bonus() const override;


    private:
    };

} // Logic

#endif //PROJECTPACMAN_FRUIT_H
