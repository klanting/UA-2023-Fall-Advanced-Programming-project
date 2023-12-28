//
// Created by tibov on 25/12/23.
//

#include "Memento.h"
#include "Matrix.h"
#include "Cell.h"

    namespace Logic::WFC {

        template class Memento<Matrix<Cell>>;

        template<typename T>
        Memento<T>::Memento(T data): data{data} {

        }

        template<typename T>
        T Memento<T>::getData() const {
            return data;
        }

    } // WFC
// Logic