//
// Created by tibov on 25/12/23.
//

#ifndef PROJECTPACMAN_WFCWORLDGENERATOR_H
#define PROJECTPACMAN_WFCWORLDGENERATOR_H
#include "TypeRuleManager.h"
#include "Cell.h"
#include "CellChangeLog.h"
namespace Logic {
    namespace WFC {

        class WFCWorldGenerator {
        public:
            WFCWorldGenerator();
            void print() const;
            void printKey(bool simple=false) const;
            void exportData() const;
        private:
            bool place(int i, int j, int type);

            void generate();
            void generateOutsideWall();
            bool propagate(int i, int j, const Cell& c);

            std::vector<Vector2D<int>> lowestEntropy();
            std::vector<Vector2D<int>> largestExpansion(const std::vector<Vector2D<int>>& ex);

            TypeRuleManager type_manager;

            const int grid_width = 19;
            const int grid_height = 9;

            Matrix<Cell> grid;

            CellChangeLog cl;

        };

    } // WFC
} // Logic

#endif //PROJECTPACMAN_WFCWORLDGENERATOR_H
