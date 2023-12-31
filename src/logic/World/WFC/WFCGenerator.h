//
// Created by tibov on 25/12/23.
//

#ifndef PROJECTPACMAN_WFCGENERATOR_H
#define PROJECTPACMAN_WFCGENERATOR_H
#include "Matrix.h"
#include <vector>
#include "../../Vector2D.h"
#include <memory>
#include "WFCGridGenerator.h"
#include "../WorldLoader.h"

    namespace Logic::WFC {

        class WFCGenerator: public WorldLoading::WorldLoader{
        public:
            WFCGenerator(std::unique_ptr<AbstractFactory>&& factory, const std::shared_ptr<Score>& score);
            std::unique_ptr<World> load(double difficulty, int lives) override;
        private:
            void readMatrix();
            bool check(const Vector2D<int>& start_pos, const Vector2D<int>& direction);
            void addWall(const Vector2D<int>& start_pos, const Vector2D<int>& size);
            void addIntersection(const Vector2D<int>& start_pos);
            void addCoin(const Vector2D<int>& start_pos);

            void createWall(int i, int j);

            Matrix<int> m;
            std::unique_ptr<Vector2D<>> ghost_spawn;

            Vector2D<> offset = {0.025, 0.075};

            std::shared_ptr<EntityModel> pacman;
            std::vector<std::shared_ptr<EntityModel>> entities;
            std::vector<std::shared_ptr<EntityModel>> not_passable;
            std::vector<std::shared_ptr<EntityModel>> intersection;

            WFCGridGenerator grid_gen;
            int consumable_count = 0;
        };

    } // WFC
// Logic

#endif //PROJECTPACMAN_WFCGENERATOR_H
