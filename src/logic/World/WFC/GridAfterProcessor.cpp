//
// Created by tibov on 28/12/23.
//

#include "GridAfterProcessor.h"


    namespace Logic::WFC {
        GridAfterProcessor::GridAfterProcessor(const Matrix<int> &simplified_grid, const std::vector<Vector2D<int>>& directions): simplified_grid{simplified_grid}, directions{directions} {

        }


        void GridAfterProcessor::fixSingleWall() {
            //detect which walls are single
            std::vector<Vector2D<int>> singles;
            std::vector<Vector2D<int>> blocked;
            for (int j = 1; j<simplified_grid.getHeight()-1; j++){
                for (int i = 1; i<simplified_grid.getWidth()-1; i++){
                    if (simplified_grid.get(i, j) == 0 && isSingleWall(i, j)){
                        singles.emplace_back(i, j);

                    }

                }
            }

            //connect neighbouring single walls, if together formed a bigger wall, we will not use this anymore
            //In that case store in blocked
            for (auto s1: singles){

                for (auto s2: singles){
                    if (std::find(blocked.begin(), blocked.end(), s1) != blocked.end()){
                        continue;
                    }
                    if (std::find(blocked.begin(), blocked.end(), s2) != blocked.end()){
                        continue;
                    }

                    if (s1.getDistance(s2) == 2 && (s1[0] == s2[0] || s1[1] == s2[1])){
                        blocked.push_back(s1);
                        blocked.push_back(s2);
                        Vector2D<int> v = (s1+s2);
                        simplified_grid.set(v[0]/2, v[1]/2, 0);
                    }
                }
            }


        }

        void GridAfterProcessor::fixLongWalls() {
            //make sure long wall intersections of format:
            //wwwwP
            //PPwPP
            //PPwPP
            //will be split up so we don't have walls connected by 3 other walls
            //this will make the maze a bit better for playability

            //check which walls are multicorner walls
            std::vector<Vector2D<int>> corners;
            for (int j = 1; j<simplified_grid.getHeight()-1; j++){
                for (int i = 1; i<simplified_grid.getWidth()-1; i++){
                    if (simplified_grid.get(i, j) == 0 && isMultiCornerWall(i, j)){
                        corners.emplace_back(i, j);

                    }

                }
            }

            //check which direction goes on for the longest, split up that direction
            for (auto c: corners){
                Vector2D<int> best_dir;
                int best_distance = 0;

                for (int i = 0; i<4; i++){
                    Vector2D<int> dir = directions[i];
                    int distance = 0;

                    Vector2D<int> loop_pos = dir+c;
                    do{
                        distance += 1;
                        loop_pos += dir;

                        if (loop_pos[0] < 0 || loop_pos[0] > simplified_grid.getWidth()-1 || loop_pos[1] < 0 || loop_pos[1] > simplified_grid.getHeight()-1){
                            break;
                        }

                    }while(simplified_grid.get(loop_pos[0], loop_pos[1]) == 0);


                    if (distance > best_distance){
                        best_distance = distance;
                        best_dir = dir;
                    }
                }
                Vector2D<int> remove_wall = c+best_dir;
                simplified_grid.set(remove_wall[0], remove_wall[1], 1);
            }

        }

        bool GridAfterProcessor::isSingleWall(int i, int j) {
            //check if an entry is a single wall
            for (int d = 0; d<4; d++){
                Vector2D<int> dir = directions[d];
                if (simplified_grid.get(i+dir[0], j+dir[1]) == 0){
                    return false;
                }
            }

            return true;
        }


        bool GridAfterProcessor::isMultiCornerWall(int i, int j) {
            //check if an entry is a Multi Corner wall (next to more than 2 walls)

            return getNeighbourCount(i, j, {0}) > 2;

        }

        bool GridAfterProcessor::allReachable() {
            //check if all walkable places in the maze are reachable
            //do basic set (kinda breath first) algorithm
            std::set<std::pair<int, int>> to_check = {std::make_pair(1, 1)};
            std::set<std::pair<int, int>> closed;

            while (!to_check.empty()){
                auto check = *to_check.begin();
                for (std::pair<int, int> n: std::vector<std::pair<int, int>>{{1, 0}, {-1, 0}, {0, 1}, {0, -1}}){
                    std::pair<int, int> new_pos = std::make_pair(n.first+check.first, n.second+check.second);
                    if (simplified_grid.get(new_pos.first, new_pos.second) == 1 && closed.find(new_pos) == closed.end()){
                        to_check.insert(new_pos);
                    }

                }

                to_check.erase(check);
                closed.insert(check);
            }


            //compare if the amount of places reached equals the amount of places that are walkable
            return closed.size() == simplified_grid.count(1);
        }

        bool GridAfterProcessor::isIntersection(int i, int j) {
            //check if a given entry is an intersection

            return getNeighbourCount(i, j, {1, 2}) > 2;
        }

        void GridAfterProcessor::applyIntersections() {
            //mark intersections on the grid
            for (int j = 1; j<simplified_grid.getHeight()-1; j++){
                for (int i = 1; i<simplified_grid.getWidth()-1; i++){
                    if (isIntersection(i, j)){
                        simplified_grid.set(i, j, 2);
                    }
                }
            }


        }

        bool GridAfterProcessor::IntersectionConflicts() {
            //check if 2 intersections are to close to each other
            //this will create less beautiful results
            for (int j = 1; j<simplified_grid.getHeight()-1; j++){
                for (int i = 1; i<simplified_grid.getWidth()-1; i++){
                    if (isIntersection(i, j)){
                        for (std::pair<int, int> n: std::vector<std::pair<int, int>>{{1, 0}, {-1, 0}, {0, 1}, {0, -1}}){
                            std::pair<int, int> new_pos = std::make_pair(n.first+i, n.second+j);
                            if (isIntersection(new_pos.first, new_pos.second)){
                                return true;
                            }

                        }
                    }
                }
            }
            return false;
        }

        bool GridAfterProcessor::doAfterProcessing() {
            //fix walls and check if we want this grid
            fixSingleWall();
            fixLongWalls();

            bool all_reachable = allReachable();

            applyIntersections();

            bool intersect_conflict = IntersectionConflicts();

            return all_reachable && !intersect_conflict;
        }

        Matrix<int> GridAfterProcessor::getSimplifiedGrid() const {
            return simplified_grid;
        }

        int GridAfterProcessor::getNeighbourCount(int i, int j, const std::set<int> &options) {
            //give the count of neighbours that are part of the options
            std::vector<bool> suc6;

            if (options.find(simplified_grid.get(i, j)) == options.end()){
                return false;
            }
            suc6.push_back(options.find(simplified_grid.get(i, j+1)) != options.end());
            suc6.push_back(options.find(simplified_grid.get(i, j-1)) != options.end());
            suc6.push_back(options.find(simplified_grid.get(i+1, j)) != options.end());
            suc6.push_back(options.find(simplified_grid.get(i-1, j)) != options.end());

            return (int) std::count(suc6.begin(), suc6.end(), true);
        }

    } // WFC
// Logic