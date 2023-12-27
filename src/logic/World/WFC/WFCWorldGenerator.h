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

            std::vector<Vector2D<int>> lowestEntropy();
            std::vector<Vector2D<int>> largestExpansion(const std::vector<Vector2D<int>>& ex);

            std::unique_ptr<TypeRuleManager> type_manager;

            std::vector<Vector2D<int>> directions;

            const int grid_width = 20;
            const int grid_height = 11;

            Matrix<Cell> grid;

            CellChangeLog cl;

            Matrix<int> getGridSimple();

            static std::vector<Vector2D<int>> getCorners(const Matrix<int>& m);


        };

    } // WFC
} // Logic

#endif //PROJECTPACMAN_WFCWORLDGENERATOR_H
