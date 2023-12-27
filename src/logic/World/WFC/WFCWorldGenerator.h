//
// Created by tibov on 25/12/23.
//

#ifndef PROJECTPACMAN_WFCWORLDGENERATOR_H
#define PROJECTPACMAN_WFCWORLDGENERATOR_H
#include "TypeRuleManager.h"
#include "Cell.h"
#include "CellChangeLog.h"
#include "Converter.h"
#include "../../Random.h"
#include <memory>
namespace Logic {
    namespace WFC {

        class WFCWorldGenerator {
        public:
            WFCWorldGenerator();
            void print(bool simple=false) const;
            void printKey(bool simple=false) const;
            void exportData() const;
            void load();

        private:
            bool place(int i, int j, int type);

            void generate();
            void generateGhostSpawn();
            void generateOutsideWall();
            bool propagate(int i, int j, const Cell& c);
            void fixSingleWall();
            void fixLongWalls();

            std::vector<Vector2D<int>> lowestEntropy();
            std::vector<Vector2D<int>> largestExpansion(const std::vector<Vector2D<int>>& ex);

            bool isMultiCornerWall(Matrix<int> &m, int i, int j);

            std::unique_ptr<TypeRuleManager> type_manager;

            std::vector<Vector2D<int>> directions;

            const int grid_width = 20;
            const int grid_height = 11;

            Matrix<Cell> grid;
            Matrix<int> simplified_grid;

            CellChangeLog cl;

            void getGridSimple();

            bool isSingleWall(Matrix<int>& m, int i, int j);

            bool regenerate();

            bool allReachable();
        };

    } // WFC
} // Logic

#endif //PROJECTPACMAN_WFCWORLDGENERATOR_H
