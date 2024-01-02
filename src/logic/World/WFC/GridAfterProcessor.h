//
// Created by tibov on 28/12/23.
//

#ifndef PROJECTPACMAN_GRIDAFTERPROCESSOR_H
#define PROJECTPACMAN_GRIDAFTERPROCESSOR_H
#include "Matrix.h"
#include "../../Vector2D.h"
#include <algorithm>
#include <set>
    namespace Logic::WFC {
        /**
         * this class will handle the after processing after a grid has been generated
         * will do some cleanup for better map results and checks to see if everything is reachable
         * */
        class GridAfterProcessor {
        public:
            explicit GridAfterProcessor(const Matrix<int>& simplified_grid, const std::vector<Vector2D<int>>& directions);

            [[nodiscard]] Matrix<int> getSimplifiedGrid() const;

            bool doAfterProcessing();
        private:

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
             * Checks if the wall on the given position is a stand AloneWall
             * */
            bool isSingleWall(int i, int j);

            /**
             * Check if on the given position is a wall connecting
             * with more than 2 walls on his AXIS-en
             * */
            bool isMultiCornerWall(int i, int j);

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

            /**
             * A simplified grid to do operations without needing to check to much
             * */
            Matrix<int> simplified_grid;

            std::vector<Vector2D<int>> directions;

            /**
             * gets the count of neighbours being a part of the options
             * */
             int getNeighbourCount(int i, int j, const std::set<int>& options);
        };

    } // WFC
// Logic

#endif //PROJECTPACMAN_GRIDAFTERPROCESSOR_H
