//
// Created by tibov on 25/12/23.
//

#ifndef PROJECTPACMAN_WFCGRIDGENERATOR_H
#define PROJECTPACMAN_WFCGRIDGENERATOR_H
#include "TypeRuleManager.h"
#include "Cell.h"
#include "CellChangeLog.h"
#include "../../Random.h"
#include <memory>

    namespace Logic::WFC {

        class WFCGridGenerator {
        public:
            WFCGridGenerator();
            Matrix<int> generateGridMap();

            [[nodiscard]] Matrix<Cell> save() const;
            void restore(const Matrix<Cell>& c);

        private:
            bool place(int i, int j, int type);

            void generate();
            void generateGhostSpawn();
            void generateOutsideWall();
            bool propagate(int i, int j, const Cell& c);
            void fixSingleWall();
            void fixLongWalls();

            std::vector<Vector2D<int>> lowestEntropy();

            static bool isMultiCornerWall(Matrix<int> &m, int i, int j);

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
            bool isIntersection(int i, int j);
            void applyIntersections();

            bool IntersectionConflicts();
        };

    } // WFC
// Logic

#endif //PROJECTPACMAN_WFCGRIDGENERATOR_H
