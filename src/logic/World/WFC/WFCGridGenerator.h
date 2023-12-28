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
            /**
             * Constructor for the GridGenerator
             * */
            WFCGridGenerator();

            /**
             * regenerate a GridMap
             * */
            Matrix<int> generateGridMap();

            /**
             * Save function to work with the Memento Design Pattern
             * */
            [[nodiscard]] Matrix<Cell> save() const;

            /**
             * Restore function to work with the Memento Design Pattern
             * */
            void restore(const Matrix<Cell>& c);

        private:
            /**
             * Change a cell its value and propagate all the other cells
             * based on these changes
             * */
            bool place(int i, int j, int type);

            /**
             * Do generation of the grid map based on the type rules
             * */
            void generate();

            /**
             * Place the ghostSpawn in the map
             * */
            void generateGhostSpawn();

            /**
             * Guarantees that only types on the outside of the map can be on the outside
             * */
            void generateOutsideWall();

            /**
             * propagate the cells
             * This function will be executed recursively
             * as input we give the cell that will be on the given position
             * propagate will make sure that all the neighbouring cells will be allowed
             * This will be recursively because
             * change 1 -> a certain position can only have 1 type -> some of these neighbours will also have more restrictions
             * and so on
             * */
            bool propagate(int i, int j, const Cell& c);

            /**
             * After processing:
             * If a couple single walls are next to each other, connect those
             * */
            void fixSingleWall();

            /**
             * If walls have wall corners connection with more than 2 walls
             * We will split the these up, this ensures better results
             * */
            void fixLongWalls();

            /**
             * Get the cell with the lowest Entropy
             * */
            std::vector<Vector2D<int>> lowestEntropy();

            /**
             * Check if on the given position is a wall connecting
             * with more than 2 walls on his AXIS-en
             * */
            bool isMultiCornerWall(int i, int j);

            /**
             * ptr to TypeRuleManager we will use to understand the TypeRules
             * */
            std::unique_ptr<TypeRuleManager> type_manager;

            /**
             * All the directions we use to determine our rules and Cell propagate impact
             * */
            std::vector<Vector2D<int>> directions;

            /**
             * grid size of the grid that we are going to generate
             * */
            const int grid_width = 20;
            const int grid_height = 11;

            /**
             * Grid of Cells
             * */
            Matrix<Cell> grid;

            /**
             * A simplified grid to do operations without needing to check to much
             * */
            Matrix<int> simplified_grid;

            /**
             * CellChangeLog will be the CareGiver of the Memento Design Pattern
             * */
            CellChangeLog cl;

            /**
             * generate the simplified grid
             * */
            void getGridSimple();

            /**
             * Checks if the wall on the given position is a stand AloneWall
             * */
            bool isSingleWall(int i, int j);

            /**
             * This function will generate a new GridMap
             * */
            bool regenerate();

            /**
             * Checks if every location is reachable
             * */
            bool allReachable();

            /**
             * Check if a given entity is an intersection
             * */
            bool isIntersection(int i, int j);

            /**
             * Mark the intersections
             * */
            void applyIntersections();

            /**
             * Checks if their are intersection conflicts,
             * These are just situations that will make less beautiful/practical maps
             * */
            bool IntersectionConflicts();
        };

    } // WFC
// Logic

#endif //PROJECTPACMAN_WFCGRIDGENERATOR_H
