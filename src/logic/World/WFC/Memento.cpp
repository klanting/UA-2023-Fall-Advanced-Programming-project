//
// Created by tibov on 25/12/23.
//

#include "Memento.h"

namespace Logic {
    namespace WFC {

        template<typename T>
        Memento<T>::Memento(T data): data{data} {

        }

        template<typename T>
        T Memento<T>::getData() const {
            return data;
        }

    } // WFC
} // Logic