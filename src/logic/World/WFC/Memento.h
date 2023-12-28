//
// Created by tibov on 25/12/23.
//

#ifndef PROJECTPACMAN_MEMENTO_H
#define PROJECTPACMAN_MEMENTO_H


    namespace Logic::WFC {
        /**
         * part of Design Pattern: Memento
         * this class will store 1 moment of a state
         * */
        template<typename T>
        class Memento {
        public:
            explicit Memento(T data);
            virtual T getData() const;
            virtual ~Memento()  = default;
        private:
            T data;

        };




    } // WFC
// Logic

#endif //PROJECTPACMAN_MEMENTO_H
