//
// Created by tibov on 25/12/23.
//

#include "CellChangeLog.h"

namespace Logic {
    namespace WFC {
        void CellChangeLog::save(const Matrix<Cell> &m) {
            history.push(Memento(m));

        }

        Matrix<Cell> CellChangeLog::undo() {
            auto m = history.top().getData();
            history.pop();
            return m;
        }
    } // WFC
} // Logic