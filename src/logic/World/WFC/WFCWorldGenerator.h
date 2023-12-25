//
// Created by tibov on 25/12/23.
//

#ifndef PROJECTPACMAN_WFCWORLDGENERATOR_H
#define PROJECTPACMAN_WFCWORLDGENERATOR_H
#include "TypeRuleManager.h"
#include "Cell.h"
#include "CellChangeLog.h"
#include "Converter.h"
namespace Logic {
    namespace WFC {

        class WFCWorldGenerator {
        public:
            WFCWorldGenerator();
            void print() const;
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

            TypeRuleManager type_manager;

            const int grid_width = 20;
            const int grid_height = 11;

            Matrix<Cell> grid;

            CellChangeLog cl;

            Matrix<int> getGridSimple();


        };

    } // WFC
} // Logic

#endif //PROJECTPACMAN_WFCWORLDGENERATOR_H
