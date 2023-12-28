//
// Created by tibov on 25/12/23.
//

#include "CellChangeLog.h"
#include "WFCGridGenerator.h"

    namespace Logic::WFC {
        void CellChangeLog::save() {
            history.push(CellMemento(generator.save()));

        }

        void CellChangeLog::undo() {
            auto m = history.top().getData();
            history.pop();
            generator.restore(m);
        }

        CellChangeLog::CellChangeLog(WFCGridGenerator &generator): generator{generator} {

        }
    } // WFC
// Logic