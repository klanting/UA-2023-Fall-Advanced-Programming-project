//
// Created by tibov on 25/12/23.
//

#include "WFCWorldGenerator.h"
#include "../../Vector2D.h"
namespace Logic {
    namespace WFC {
        WFCWorldGenerator::WFCWorldGenerator(): directions{Logic::Vector2D<int>{1, 0}, Logic::Vector2D<int>{-1, 0}, Logic::Vector2D<int>{0, 1}, Logic::Vector2D<int>{0, -1},
                                                           Logic::Vector2D<int>{1, 1}, Logic::Vector2D<int>{-1, 1}, Logic::Vector2D<int>{1, -1}, Logic::Vector2D<int>{-1, -1}},
                                                           grid{grid_width, grid_height, Cell{17}} {


            type_manager = std::make_unique<TypeRuleManager>("WFC/sampleData.WFC", directions);

            generateOutsideWall();
            generateGhostSpawn();

            generate();
        }

        void WFCWorldGenerator::generate() {
            for (int h = 0; h<500; h++){
                auto v_options = lowestEntropy();

                if (v_options.empty()){
                    break;
                }

                v_options = largestExpansion(v_options);


                int v_index = Random::getInstance()->getRandomIndex(0, v_options.size()-1);
                auto p = v_options[v_index];

                std::set<int> o = grid.get(p[0], p[1]).getOptions();
                if (o.empty()){

                    std::cout << "broke2" << std::endl;
                    continue;
                }

                int rand_index = Random::getInstance()->getRandomIndex(0, o.size()-1);

                auto it = o.begin();
                for (int i = 0; i<rand_index; i++){
                    it++;
                }

                cl.save(grid);
                bool suc6 = place(p[0], p[1], *it);
                if (!suc6){
                    grid = cl.undo();

                    Cell to_change = grid.get(p[0], p[1]);
                    to_change.remove(*it);
                    grid.set(p[0], p[1], to_change);
                    bool s2 = propagate(p[0], p[1], to_change);
                    if (!s2){
                        throw "oei";
                    }

                    std::cout << "broke" << std::endl;
                    continue;
                }
            }


        }

        void WFCWorldGenerator::generateOutsideWall() {
            for (int j = 0; j<grid_height; j++){

                for (int i = 0; i<grid_width; i++){
                    if (i > 0 && i < grid_width-1 && j > 0 && j < grid_height-1){
                        continue;
                    }

                    int val = 0;

                    if (j != 0 && j != grid_height-1){
                        val = 1;
                    }


                    if (i == 0 && j == 0){
                        val = 2;
                    }

                    if (i == grid_width-1 && j == 0){
                        val = 3;
                    }

                    if (i == 0 && j == grid_height-1){
                        val = 4;
                    }

                    if (i == grid_width-1 && j == grid_height-1){
                        val = 5;
                    }



                    place(i, j, val);

                }
            }

        }

        bool WFCWorldGenerator::place(int i, int j, int type) {
            Cell c = grid.get(i, j);
            c.place(type);
            grid.set(i, j, c);

            return propagate(i, j, c);

        }

        bool WFCWorldGenerator::propagate(int i, int j, const Cell &c) {

            std::vector<Vector2D<int>> directions = {Logic::Vector2D{1, 0}, Logic::Vector2D{-1, 0}, Logic::Vector2D{0, 1}, Logic::Vector2D{0, -1},
                                                     Logic::Vector2D{1, 1}, Logic::Vector2D{-1, 1}, Logic::Vector2D{1, -1}, Logic::Vector2D{-1, -1}};

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

        void WFCWorldGenerator::print(bool simple) const {
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

        void WFCWorldGenerator::printKey(bool simple) const {
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

        std::vector<Vector2D<int>> WFCWorldGenerator::lowestEntropy() {
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

        std::vector<Vector2D<int>> WFCWorldGenerator::largestExpansion(const std::vector<Vector2D<int>> &ex) {
            std::vector<Vector2D<int>> options;
            for (auto p: ex){
                std::set<int> o = grid.get(p[0], p[1]).getOptions();
                if (o.size() > 1 || *(o.begin()) > 5){
                    options.push_back(p);
                }

            }

            if (options.empty()){
                options = ex;
            }

            return ex;
        }

        void WFCWorldGenerator::exportData() const {
            std::ofstream file("WFC/output");
            for (int j = 0; j<grid_height; j++){
                for (int i = 0; i<grid_width; i++){
                    if(grid.get(i, j).getKey() <= 5){
                        file << 'w';
                    }else{
                        file << 'P';
                    }
                }
                file << '\n';
            }

            file.close();

        }

        Matrix<int> WFCWorldGenerator::getGridSimple() {
            Matrix<int> m (grid_width, grid_height, 0);
            for (int j = 0; j<grid_height; j++){
                for (int i = 0; i<grid_width; i++){

                    int val = 1;
                    if(grid.get(i, j).getKey() <= 5 && grid.get(i, j).getKey() >= 0){
                        val = 0;
                    }

                    if (grid.get(i, j).getKey() < 0){
                        val = grid.get(i, j).getKey();
                    }

                    m.set(i, j, val);
                }
            }


            return m;
        }

        void WFCWorldGenerator::load() {
            auto m = getGridSimple();
            Converter c(m);
            c.exportData();

        }

        void WFCWorldGenerator::generateGhostSpawn() {
            int rand_i = Random::getInstance()->getRandomIndex(0,  (grid_width-2)/2 -1)*2+1;
            int rand_j = Random::getInstance()->getRandomIndex(0,  (grid_height-2)/2 -1)*2+1;


            std::vector<Vector2D<int>> options = {};


            if (rand_j != 1){
                options.push_back(Vector2D<int>{0, -1});
            }

            if (rand_j != grid_height-2){
                options.push_back(Vector2D<int>{0, 1});
            }

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


    } // WFC
} // Logic