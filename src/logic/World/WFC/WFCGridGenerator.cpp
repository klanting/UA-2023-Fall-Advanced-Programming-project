//
// Created by tibov on 25/12/23.
//

#include "WFCGridGenerator.h"

    namespace Logic::WFC {
        WFCGridGenerator::WFCGridGenerator(): directions{Logic::Vector2D<int>{1, 0}, Logic::Vector2D<int>{0, 1}, Logic::Vector2D<int>{-1, 0}, Logic::Vector2D<int>{0, -1},
                                                         Logic::Vector2D<int>{1, 1}, Logic::Vector2D<int>{-1, 1}, Logic::Vector2D<int>{-1, -1}, Logic::Vector2D<int>{1, -1}},
                                                         cl{*this}, GridGenerator{} {


            type_manager = std::make_unique<TypeRuleManager>("WFC/sampleData.WFC", directions);


            grid = Matrix<Cell>{grid_width, grid_height, Cell{type_manager->getCharAmount()}};
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
                int rand_index = Random::getInstance()->getRandomIndex(0, (int) o.size()-1);

                auto it = o.begin();
                for (int i = 0; i<rand_index; i++){
                    it++;
                }

                //apply the changes
                //if the changes cause a contradiction
                //rollback till before the changes
                //remove the possibility that we just tried and go back to the start
                cl.save();
                bool suc6 = place(p[0], p[1], *it);
                if (!suc6){
                    cl.undo();

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
            //places a type on a cell and propagate the changes
            Cell c = grid.get(i, j);
            c.place(type);
            grid.set(i, j, c);

            return propagate(i, j, c);

        }

        bool WFCGridGenerator::propagate(int i, int j, const Cell &c) {

            //make changes to all the other neighbours
            for (int dir = 0; dir<directions.size(); dir++){
                auto p = directions[dir];
                if (j+p[1] < 0 || j+p[1] >= grid_height){
                    continue;
                }
                if (i+p[0] < 0 || i+p[0] >= grid_width){
                    continue;
                }

                //all options a neighbour of cell c can still have
                std::set<int> n_options;

                for (auto o: c.getOptions()){
                    std::set<int> n_temp = type_manager->getOptions(o, dir);
                    n_options.insert(n_temp.begin(), n_temp.end());
                }

                //change its value
                Cell n = grid.get(i+p[0], j+p[1]);
                bool recur = n.updateValue(n_options);
                grid.set(i+p[0], j+p[1], n);

                //if something changed, to recursive changes
                if (recur){
                    bool suc6 = propagate(i+p[0], j+p[1], n);
                    if (!suc6){
                        return false;
                    }
                }

                //return falls is contrdiction
                if (n.getEntropy() == 0 && !n.isDefined()){
                    return false;
                }
            }

            return true;

        }


        std::vector<Vector2D<int>> WFCGridGenerator::lowestEntropy() {
            //store a set of all the locations with the lowest Entropy
            std::vector<Vector2D<int>> best_options;
            double best_entropy = std::numeric_limits<double>::infinity();

            for (int j = 0; j<grid_height; j++){
                for (int i = 0; i<grid_width; i++){
                    if (grid.get(i, j).isDefined()){
                        continue;
                    }

                    double v = grid.get(i, j).getEntropy();

                    //if lower entropy make new lowest and start being only value in set
                    if (v < best_entropy){
                        best_entropy = v;
                        best_options.clear();
                        best_options.emplace_back(i, j);
                    }

                    //if same entropy as lowest, add to set
                    if (v == best_entropy){
                        best_options.emplace_back(i, j);
                    }

                }
            }
            return best_options;
        }


        Matrix<int>WFCGridGenerator::getGridSimple() const{
            //get a simplified grid of the Cell grid
            // simplified:
            // walls -> 1
            // rest 0
            Matrix<int> simplified_grid{grid_width, grid_height, 0};
            for (int j = 0; j<grid_height; j++){
                for (int i = 0; i<grid_width; i++){

                    int val = 1;
                    if(grid.get(i, j).getKey() < type_manager->getWallCount() && grid.get(i, j).getKey() >= 0){
                        val = 0;
                    }

                    if (grid.get(i, j).getKey() < 0){
                        val = grid.get(i, j).getKey();
                    }

                    simplified_grid.set(i, j, val);
                }
            }
            return simplified_grid;
        }


        void WFCGridGenerator::generateGhostSpawn() {
            //create a GhostSpawn based on the data in the type_manager
            int rand_i = 9;
            int rand_j = 5;


            Vector2D spawn_pos = Vector2D<int>{rand_i, rand_j};
            Vector2D exit = Vector2D<int>{0, -1} + spawn_pos;

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
            for (std::pair<int, Vector2D<int>> p: type_manager->getSpawnData()){
                Vector2D pos = spawn_pos + p.second;
                if (pos == exit){
                    continue;
                }


                cl.save();
                bool suc6 = place(pos[0], pos[1], p.first);

                if (!suc6){
                    cl.undo();
                }
            }

        }


        std::pair<bool, Matrix<int>> WFCGridGenerator::regenerate() {
            grid.clear(Cell{type_manager->getCharAmount()});
            generateOutsideWall();
            generateGhostSpawn();

            generate();

            auto simplified_grid = getGridSimple();
            GridAfterProcessor gap{simplified_grid, directions};
            bool suc6 = gap.doAfterProcessing();

            return std::make_pair(suc6, gap.getSimplifiedGrid());

        }



        Matrix<int> WFCGridGenerator::generateGridMap(){
            bool suc6 = false;
            Matrix<int> simplified_grid{0, 0, 0};
            while (!suc6){
                auto p = regenerate();
                suc6 = p.first;
                simplified_grid = p.second;
            }

            return simplified_grid;
        }



    } // WFC
// Logic