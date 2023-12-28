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

        /**
         * Reads self invented file format .WFC
         * This file will be used to generate patterns similar to the pattern present in the File
         * */
        class WFCReader {
        public:
            /**
             * constructor for WFC Reader
             * */
            explicit WFCReader(const std::string& file_path);

            /**
             * getter for the amount of wall tokens present in the file
             * */
            [[nodiscard]] int getWallCount() const;

            /**
             * getter for the amount of tokens present in the file
             * */
            [[nodiscard]] int getIdCounter() const;

            /**
             * getter for the width of the grid present in the file
             * */
            [[nodiscard]] int getDataWidth() const;

            /**
             * getter for the height of the grid present in the file
             * */
            [[nodiscard]] int getDataHeight() const;

            /**
             * getter for the Grid read from the File
             * */
            [[nodiscard]] Matrix<int> getGrid() const;

        private:
            /**
             * read wall count symbols from file
             * */
            void readWallCount();

            /**
             * read the number on the current line of the file
             * */
            void readNumber(int& n);

            /**
             * read the grid on the file
             * */
            void readGrid();
            int wall_count;
            int data_width;
            int data_height;

            /**
             * map char token of file to type index
             * */
            std::map<char, int> count_table;
            Matrix<int> buffer;
            std::ifstream file;
            int id_counter;


        };

    } // WFC
// Logic

#endif //PROJECTPACMAN_WFCREADER_H
