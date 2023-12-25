//
// Created by tibov on 25/12/23.
//

#ifndef PROJECTPACMAN_MEMENTO_H
#define PROJECTPACMAN_MEMENTO_H

namespace Logic {
    namespace WFC {

        template<typename T>
        class Memento {
        public:
            Memento(T data);
            virtual T getData() const;
        private:
            T data;

        };




    } // WFC
} // Logic

#endif //PROJECTPACMAN_MEMENTO_H
