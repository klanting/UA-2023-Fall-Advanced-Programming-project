//
// Created by tibov on 25/12/23.
//

#include "WFCWorldGenerator.h"
#include "../../Vector2D.h"
namespace Logic {
    namespace WFC {
        WFCWorldGenerator::WFCWorldGenerator(): type_manager{"WFC/sampleData.WFC", {Logic::Vector2D<int>{1, 0}, Logic::Vector2D<int>{-1, 0}, Logic::Vector2D<int>{0, 1}, Logic::Vector2D<int>{0, -1},
                                                                                    Logic::Vector2D<int>{1, 1}, Logic::Vector2D<int>{-1, 1}, Logic::Vector2D<int>{1, -1}, Logic::Vector2D<int>{-1, -1}}}, grid{grid_width, grid_height, Cell{11}} {

            generateOutsideWall();
            generate();
        }

        void WFCWorldGenerator::generate() {
            srand(time(NULL));

            for (int h = 0; h<100; h++){
                auto v_options = lowestEntropy();

                if (v_options.empty()){
                    break;
                }

                int v_index = rand() % v_options.size();
                auto p = v_options[v_index];

                std::set<int> o = grid.get(p[0], p[1]).getOptions();
                if (o.empty()){
                    std::cout << "broke" << std::endl;
                    auto t_options = lowestEntropy();
                    break;
                }

                int rand_index = rand() % o.size();

                auto it = o.begin();
                for (int i = 0; i<rand_index; i++){
                    it++;
                }
                place(p[0], p[1], *it);
            }


        }

        void WFCWorldGenerator::generateOutsideWall() {
            for (int j = 0; j<grid_height; j++){

                for (int i = 0; i<grid_width; i++){
                    if (i > 0 && i < grid_width-1 && j > 0 && j < grid_height-1){
                        continue;
                    }

                    place(i, j, 0);

                }
            }

        }

        void WFCWorldGenerator::place(int i, int j, int type) {
            Cell c = grid.get(i, j);
            c.place(type);
            grid.set(i, j, c);

            propagate(i, j, c);

        }

        void WFCWorldGenerator::propagate(int i, int j, const Cell &c) {

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
                    std::set<int> n_temp = type_manager.getOptions(o, dir);
                    n_options.insert(n_temp.begin(), n_temp.end());
                }

                Cell n = grid.get(i+p[0], j+p[1]);
                bool recur = n.updateValue(n_options);
                grid.set(i+p[0], j+p[1], n);
                if (recur){
                    propagate(i+p[0], j+p[1], n);
                }
            }


        }

        void WFCWorldGenerator::print() const {
            for (int j = 0; j<grid_height; j++){
                for (int i = 0; i<grid_width; i++){
                    std::cout << grid.get(i, j).getEntropy() << " ";
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;
        }

        void WFCWorldGenerator::printKey() const {
            for (int j = 0; j<grid_height; j++){
                for (int i = 0; i<grid_width; i++){
                    std::cout << grid.get(i, j).getKey() << " ";
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

        void WFCWorldGenerator::exportData() const {
            std::ofstream file("WFC/output");
            for (int j = 0; j<grid_height; j++){
                for (int i = 0; i<grid_width; i++){
                    if(grid.get(i, j).getKey() == 0){
                        file << 'w';
                    }else{
                        file << 'P';
                    }
                }
                file << '\n';
            }

            file.close();

        }


    } // WFC
} // Logic