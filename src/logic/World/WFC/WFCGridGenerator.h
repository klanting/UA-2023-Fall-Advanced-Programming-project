//
// Created by tibov on 25/12/23.
//

#ifndef PROJECTPACMAN_WFCGRIDGENERATOR_H
#define PROJECTPACMAN_WFCGRIDGENERATOR_H
#include "TypeRuleManager.h"
#include "CellChangeLog.h"
#include "../../Random.h"
#include <memory>
#include "GridGenerator.h"
#include "GridAfterProcessor.h"

    namespace Logic::WFC {

        /**
         * this class will use the WFC algorithm to create a new Grid representing the pacman game
         * */
        class WFCGridGenerator: public GridGenerator{
        public:
            /**
             * Constructor for the GridGenerator
             * */
            WFCGridGenerator();

            /**
             * regenerate a GridMap
             * */
            Matrix<int> generateGridMap();

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
             * Get the cell with the lowest Entropy
             * */
            std::vector<Vector2D<int>> lowestEntropy();



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
             * CellChangeLog will be the CareGiver of the Memento Design Pattern
             * */
            CellChangeLog cl;

            /**
             * generate the simplified grid
             * of the current grid and returns that
             * */
            [[nodiscard]] Matrix<int> getGridSimple() const;


            /**
             * This function will generate a new GridMap
             * */
            std::pair<bool, Matrix<int>> regenerate();


        };

    } // WFC
// Logic

#endif //PROJECTPACMAN_WFCGRIDGENERATOR_H
