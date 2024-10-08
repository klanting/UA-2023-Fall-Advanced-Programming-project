//
// Created by tibov on 27/12/23.
//

#include "WFCReader.h"


    namespace Logic::WFC {
        WFCReader::WFCReader(const std::string &file_path): buffer{0, 0, 0}, file{file_path} {

            if (!file.good()){
                throw std::invalid_argument(file_path);
            }

            //init all var
            data_width = 0;
            data_height = 0;
            wall_count = 0;
            id_counter = 0;

            //in case wrong file format
            try{
                //read data from file
                readWallCount();
                readNumber(data_width);
                readNumber(data_height);
                Matrix<int> new_buffer{data_width, data_height, 0};
                buffer = new_buffer;
                readGrid();
                readSpawn();
                file.close();
            }catch (std::exception& e){
                throw std::invalid_argument(file_path);
            }

        }

        void WFCReader::readWallCount() {
            //read entire line
            //store every char on the line and see these char as walls
            char c = (char) file.get();
            do{
                count_table.insert({c, id_counter});
                id_counter++;

                c = (char) file.get();

            }while(c != '\n');

            wall_count = id_counter;

        }

        void WFCReader::readNumber(int &n) {
            //read the number present on this file
            std::string temp;

            char c;
            do{
                c = (char) file.get();
                temp += c;

            }while(c != '\n');

            temp.pop_back();
            n = std::stoi(temp);

        }

        void WFCReader::readGrid() {
            //read the grid in the file
            //store its data as type numbers on the buffer
            for (int j = 0; j<data_height; j++){
                for (int i = 0; i<data_width; i++){

                    char c = (char) file.get();
                    int a;

                    auto it = count_table.find(c);
                    if (it == count_table.end()){
                        count_table.insert({c, id_counter});

                        a = id_counter;
                        id_counter++;

                    }else{
                        a = it->second;
                    }

                    buffer.set(i, j, a);
                }
                file.get();
            }

        }

        int WFCReader::getWallCount() const {
            return wall_count;
        }

        int WFCReader::getIdCounter() const {
            return id_counter;
        }

        int WFCReader::getDataWidth() const {
            return data_width;
        }

        int WFCReader::getDataHeight() const {
            return data_height;
        }

        Matrix<int> WFCReader::getGrid() const {
            return buffer;
        }

        void WFCReader::readSpawn() {
            //stores data how the ghost spawn must look
            int spawn_width;
            int spawn_height;

            readNumber(spawn_width);
            readNumber(spawn_height);

            int spawn_pos_x;
            int spawn_pos_y;

            readNumber(spawn_pos_x);
            readNumber(spawn_pos_y);

            for (int j = 0; j<spawn_height; j++){
                for (int i = 0; i<spawn_width; i++){
                    char c = (char) file.get();

                    if (c == '*'){
                        continue;
                    }

                    int id = count_table.at(c);
                    ghost_spawn.emplace_back(id, Vector2D<int>{i-spawn_pos_x, j-spawn_pos_y});
                }
                file.get();
            }


        }

        std::vector<std::pair<int, Vector2D<int>>> WFCReader::getSpawnData() const {
            return ghost_spawn;
        }

    } // WFC
// Logic