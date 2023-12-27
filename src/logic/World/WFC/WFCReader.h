//
// Created by tibov on 27/12/23.
//

#ifndef PROJECTPACMAN_WFCREADER_H
#define PROJECTPACMAN_WFCREADER_H

#include <map>
#include <string>
#include "../../Vector2D.h"
#include "Matrix.h"
#include <fstream>

    namespace Logic::WFC {


        class WFCReader {
        public:
            explicit WFCReader(const std::string& file_path);

            int getWallCount() const;

            int getIdCounter() const;

            int getDataWidth() const;

            int getDataHeight() const;

            Matrix<int> getGrid() const;

        private:
            void readWallCount();
            void readNumber(int& n);
            void readGrid();
            int wall_count;
            int data_width;
            int data_height;
            std::map<char, int> count_table;
            Matrix<int> buffer;
            std::ifstream file;
            int id_counter;


        };

    } // WFC
// Logic

#endif //PROJECTPACMAN_WFCREADER_H
