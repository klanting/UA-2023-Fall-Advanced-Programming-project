//
// Created by tibov on 25/12/23.
//

#ifndef PROJECTPACMAN_CELL_H
#define PROJECTPACMAN_CELL_H

#include "vector"
#include "string"
#include <map>
#include <set>
#include <fstream>
#include <algorithm>
#include <iostream>


    namespace Logic::WFC {

        /**
         * Cell represent 1 position on a WFC grid
         * This Cell will be used to easily manipulate and store data that is used for the WFC algorithm
         * */
        class Cell {
        public:
            /**
             * Constructor for Cell
             * size is the amount of different type options
             * At the start all options will be fine
             * */
            explicit Cell(int size);

            /**
             * this cell will be determined and so it will store a type
             * */
            void place(int type);

            /**
             * Chance the options based on the acceptable options that it can be
             * Because of earlier calls its own options can already be narrowed down
             * so the resulting options will be the intersection between options and acceptable
             * */
            bool updateValue(const std::set<int>& acceptable);

            /**
             * get the Entropy value of this Cell
             * */
            [[nodiscard]] double getEntropy() const;

            /**
             * get the key value of the cell
             * This will give an int that will say which type this Cell is
             * */
            [[nodiscard]] int getKey() const;

            /**
             * checks if this Cell is already defined
             * */
            [[nodiscard]] bool isDefined() const;

            /**
             * Get all the options of types this Cell can be
             * */
            [[nodiscard]] const std::set<int> &getOptions() const;

            /**
             * remove a certain type as option
             * */
            void remove(int i);

            /**
             * check if 2 cells are equal to each other
             * */
            bool operator==(const Cell& other);

        private:
            /**
             * bool to state if the Cell is yet defined
             * */
            bool defined = false;

            /**
             * Set of type options still available
             * if defined this will only contain the type it is defined as
             * */
            std::set<int> options;

            /**
             * entropy value
             * */
            int entropy = -1;

            /**
             * key value that is assigned to this Cell
             * */
            int key = -1;



        };

    } // WFC
// Logic

#endif //PROJECTPACMAN_CELL_H
