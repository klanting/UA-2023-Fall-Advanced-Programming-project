//
// Created by tibov on 25/12/23.
//

#ifndef PROJECTPACMAN_WFCWORLDGENERATOR_H
#define PROJECTPACMAN_WFCWORLDGENERATOR_H
#include "TypeRuleManager.h"
#include "Cell.h"
namespace Logic {
    namespace WFC {

        class WFCWorldGenerator {
        public:
            WFCWorldGenerator();
            void print() const;
            void printKey() const;
            void exportData() const;
        private:
            void place(int i, int j, int type);

            void generate();
            void generateOutsideWall();
            void propagate(int i, int j, const Cell& c);

            std::vector<Vector2D<int>> lowestEntropy();

            TypeRuleManager type_manager;

            const int grid_width = 11;
            const int grid_height = 11;

            Matrix<Cell> grid;

        };

    } // WFC
} // Logic

#endif //PROJECTPACMAN_WFCWORLDGENERATOR_H
