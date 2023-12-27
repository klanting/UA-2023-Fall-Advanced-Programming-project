//
// Created by tibov on 25/12/23.
//

#include "WFCGridGenerator.h"
#include "../../Vector2D.h"
namespace Logic {
    namespace WFC {
        WFCGridGenerator::WFCGridGenerator(): directions{Logic::Vector2D<int>{1, 0}, Logic::Vector2D<int>{0, 1}, Logic::Vector2D<int>{-1, 0}, Logic::Vector2D<int>{0, -1},
                                                         Logic::Vector2D<int>{1, 1}, Logic::Vector2D<int>{-1, 1}, Logic::Vector2D<int>{-1, -1}, Logic::Vector2D<int>{1, -1}},
                                              grid{grid_width, grid_height, Cell{0}}, simplified_grid(grid_width, grid_height, 0) {


            type_manager = std::make_unique<TypeRuleManager>("WFC/sampleData.WFC", directions);

            bool suc6 = false;
            while (!suc6){
                suc6 = regenerate();
            }

        }

        void WFCGridGenerator::generate() {
            while (true){
                //get the grid positions of the Cells with the lowest Entropy
                auto v_options = lowestEntropy();

                if (v_options.empty()){
                    break;
                }

                //take a random Cell of these cells to continue with
                int v_index = Random::getInstance()->getRandomIndex(0, (int) v_options.size()-1);
                auto p = v_options[v_index];

                //Get alle possible type Id's this Cell can have
                std::set<int> o = grid.get(p[0], p[1]).getOptions();

                //In case we have a never resolvable conflict
                if (o.empty()){
                    break;
                }

                //take a random cell type
                int rand_index = Random::getInstance()->getRandomIndex(0, o.size()-1);

                auto it = o.begin();
                for (int i = 0; i<rand_index; i++){
                    it++;
                }

                //apply the changes
                //if the changes cause a contradiction
                //rollback till before the changes
                //remove the possibility that we just tried and go back to the start
                cl.save(grid);
                bool suc6 = place(p[0], p[1], *it);
                if (!suc6){
                    grid = cl.undo();

                    Cell to_change = grid.get(p[0], p[1]);
                    to_change.remove(*it);
                    grid.set(p[0], p[1], to_change);
                    propagate(p[0], p[1], to_change);
                    continue;
                }
            }


        }

        void WFCGridGenerator::generateOutsideWall() {
            //function for setting the outside walls
            //this ensures that the map will be closed

            Cell cell{type_manager->getCharAmount()};
            cell.place(type_manager->getCharAmount()-1);

            for (int j = -1; j<=grid_height; j++){

                for (int i = -1; i<=grid_width; i++){
                    if (i >= 0 && i < grid_width && j >= 0 && j < grid_height){
                        continue;
                    }

                    propagate(i, j, cell);

                }
            }



        }

        bool WFCGridGenerator::place(int i, int j, int type) {
            Cell c = grid.get(i, j);
            c.place(type);
            grid.set(i, j, c);

            return propagate(i, j, c);

        }

        bool WFCGridGenerator::propagate(int i, int j, const Cell &c) {

            for (int dir = 0; dir<directions.size(); dir++){
                auto p = directions[dir];
                if (j+p[1] < 0 || j+p[1] >= grid_height){
                    continue;
                }
                if (i+p[0] < 0 || i+p[0] >= grid_width){
                    continue;
                }

                std::set<int> n_options;

                for (auto o: c.getOptions()){
                    std::set<int> n_temp = type_manager->getOptions(o, dir);
                    n_options.insert(n_temp.begin(), n_temp.end());
                }

                Cell n = grid.get(i+p[0], j+p[1]);
                bool recur = n.updateValue(n_options);
                grid.set(i+p[0], j+p[1], n);
                if (recur){
                    bool suc6 = propagate(i+p[0], j+p[1], n);
                    if (!suc6){
                        return false;
                    }
                }

                if (n.getEntropy() == 0 && !n.isDefined()){
                    return false;
                }
            }

            return true;

        }

        void WFCGridGenerator::print(bool simple) const {
            for (int j = 0; j<grid_height; j++){
                for (int i = 0; i<grid_width; i++){
                    if (!simple){
                        std::cout << grid.get(i, j).getEntropy() << " ";
                    }else{
                        if(grid.get(i, j).isDefined()){
                            std::cout << 2 << " ";
                        }else if (grid.get(i, j).getEntropy() == 0){
                            std::cout << 0 << " ";
                        }else{
                            std::cout << 1 << " ";
                        }
                    }

                }
                std::cout << std::endl;
            }
            std::cout << std::endl;
        }

        void WFCGridGenerator::printKey(bool simple) const {
            for (int j = 0; j<grid_height; j++){
                for (int i = 0; i<grid_width; i++){
                    int val = grid.get(i, j).getKey();
                    if (simple){
                        if (val > 5){
                            val = 1;
                        }else{
                            val = 0;
                        }
                    }

                    std::cout <<  val << " ";
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;

        }

        std::vector<Vector2D<int>> WFCGridGenerator::lowestEntropy() {
            std::vector<Vector2D<int>> best_options;
            double best_entropy = 30;

            for (int j = 0; j<grid_height; j++){
                for (int i = 0; i<grid_width; i++){
                    if (grid.get(i, j).isDefined()){
                        continue;
                    }

                    double v = grid.get(i, j).getEntropy();
                    if (v < best_entropy){
                        best_entropy = v;
                        best_options.clear();
                        best_options.push_back(Vector2D<int>{i, j});
                    }

                    if (v == best_entropy){
                        best_options.push_back(Vector2D<int>{i, j});
                    }

                }
            }
            std::cout << "best entropy " << best_entropy << std::endl;
            return best_options;
        }




        void WFCGridGenerator::getGridSimple() {
            for (int j = 0; j<grid_height; j++){
                for (int i = 0; i<grid_width; i++){

                    int val = 1;
                    if(grid.get(i, j).getKey() <= 5 && grid.get(i, j).getKey() >= 0){
                        val = 0;
                    }

                    if (grid.get(i, j).getKey() < 0){
                        val = grid.get(i, j).getKey();
                    }

                    simplified_grid.set(i, j, val);
                }
            }
        }


        void WFCGridGenerator::generateGhostSpawn() {
            int rand_i = 9;
            int rand_j = 5;


            std::vector<Vector2D<int>> options = {};
            options.push_back(Vector2D<int>{0, -1});


            Vector2D spawn_pos = Vector2D<int>{rand_i, rand_j};
            Vector2D exit = options[Random::getInstance()->getRandomIndex(0,  options.size()-1)] + spawn_pos;

            Cell spawn_cell = grid.get(spawn_pos[0], spawn_pos[1]);
            spawn_cell.place(-2);
            grid.set(spawn_pos[0], spawn_pos[1], spawn_cell);

            spawn_cell = grid.get(spawn_pos[0]+1, spawn_pos[1]);
            spawn_cell.place(-4);
            grid.set(spawn_pos[0]+1, spawn_pos[1], spawn_cell);

            Cell exit_cell = grid.get(exit[0], exit[1]);
            exit_cell.place(-3);
            grid.set(exit[0], exit[1], exit_cell);

            //make cube around spawn unless it is the exit tile
            for (std::pair<int, Vector2D<int>> p: {std::make_pair(0, Vector2D{0, -1}),
                                                   std::make_pair(0, Vector2D{0, 1}),
                                                   std::make_pair(1, Vector2D{2, 0}),
                                                   std::make_pair(1, Vector2D{-1, 0}),
                                                   std::make_pair(5, Vector2D{2, 1}),
                                                   std::make_pair(3, Vector2D{2, -1}),
                                                   std::make_pair(4, Vector2D{-1, 1}),
                                                   std::make_pair(2, Vector2D{-1, -1}),
                                                   std::make_pair(0, Vector2D{1, -1}),
                                                   std::make_pair(0, Vector2D{1, 1})}){
                Vector2D pos = spawn_pos + p.second;
                if (pos == exit){
                    continue;
                }


                cl.save(grid);
                bool suc6 = place(pos[0], pos[1], p.first);

                if (!suc6){
                    grid = cl.undo();
                }
            }

        }

        void WFCGridGenerator::fixSingleWall() {
            std::vector<Vector2D<int>> singles;
            std::vector<Vector2D<int>> blocked;
            for (int j = 1; j<grid_height-1; j++){
                for (int i = 1; i<grid_width-1; i++){
                    if (simplified_grid.get(i, j) == 0 && isSingleWall(simplified_grid, i, j)){
                        std::cout << "hep" << std::endl;
                        singles.push_back(Vector2D<int>{i, j});

                    }

                }
            }

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

        bool WFCGridGenerator::isSingleWall(Matrix<int> &m, int i, int j) {

            for (int d = 0; d<4; d++){
                Vector2D<int> dir = directions[d];
                if (m.get(i+dir[0], j+dir[1]) == 0){
                    return false;
                }
            }

            return true;
        }

        void WFCGridGenerator::fixLongWalls() {
            std::vector<Vector2D<int>> corners;
            for (int j = 1; j<grid_height-1; j++){
                for (int i = 1; i<grid_width-1; i++){
                    if (simplified_grid.get(i, j) == 0 && isMultiCornerWall(simplified_grid, i, j)){
                        std::cout << "hep" << std::endl;
                        corners.push_back(Vector2D<int>{i, j});

                    }

                }
            }

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

                        if (loop_pos[0] < 0 || loop_pos[0] > grid_width-1 || loop_pos[1] < 0 || loop_pos[1] > grid_height-1){
                            break;
                        }

                    }while(simplified_grid.get(loop_pos[0], loop_pos[1]) == 0);

                    std::cout << distance << std::endl;

                    if (distance > best_distance){
                        best_distance = distance;
                        best_dir = dir;
                    }
                }
                std::cout << "best" << best_distance << std::endl;
                Vector2D<int> remove_wall = c+best_dir;
                simplified_grid.set(remove_wall[0], remove_wall[1], 1);
            }

        }

        bool WFCGridGenerator::isMultiCornerWall(Matrix<int> &m, int i, int j) {
            std::vector<bool> suc6;

            if (m.get(i, j) != 0){
                return false;
            }
            suc6.push_back(m.get(i, j+1) == 0);
            suc6.push_back(m.get(i, j-1) == 0);
            suc6.push_back(m.get(i+1, j) == 0);
            suc6.push_back(m.get(i-1, j) == 0);

            return std::count(suc6.begin(), suc6.end(), true) > 2;

        }

        bool WFCGridGenerator::regenerate() {
            grid.clear(Cell{type_manager->getCharAmount()});
            generateOutsideWall();

            print(false);

            generateGhostSpawn();



            generate();

            getGridSimple();
            fixSingleWall();
            fixLongWalls();

            bool all_reachable = allReachable();

            applyIntersections();

            bool intersect_conflict = IntersectionConflicts();

            return all_reachable && !intersect_conflict;

        }

        bool WFCGridGenerator::allReachable() {
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


            return closed.size() == simplified_grid.count(1);
        }

        bool WFCGridGenerator::isIntersection(int i, int j) {

            std::vector<bool> suc6;

            if (simplified_grid.get(i, j) != 1 && simplified_grid.get(i, j) != 2){
                return false;
            }
            suc6.push_back(simplified_grid.get(i, j+1) == 1 || simplified_grid.get(i, j+1) == 2);
            suc6.push_back(simplified_grid.get(i, j-1) == 1 || simplified_grid.get(i, j-1) == 2);
            suc6.push_back(simplified_grid.get(i+1, j) == 1 || simplified_grid.get(i+1, j) == 2);
            suc6.push_back(simplified_grid.get(i-1, j) == 1 || simplified_grid.get(i-1, j) == 2);

            return std::count(suc6.begin(), suc6.end(), true) > 2;
        }

        void WFCGridGenerator::applyIntersections() {
            for (int j = 1; j<grid_height-1; j++){
                for (int i = 1; i<grid_width-1; i++){
                    if (isIntersection(i, j)){
                        simplified_grid.set(i, j, 2);
                    }
                }
            }


        }

        bool WFCGridGenerator::IntersectionConflicts() {
            for (int j = 1; j<grid_height-1; j++){
                for (int i = 1; i<grid_width-1; i++){
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

        Matrix<int> WFCGridGenerator::generateGridMap() {
            return simplified_grid;
        }


    } // WFC
} // Logic