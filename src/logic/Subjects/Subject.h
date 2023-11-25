//
// Created by tibov on 25/11/23.
//

#ifndef PROJECTPACMAN_SUBJECT_H
#define PROJECTPACMAN_SUBJECT_H
#include "../Vector2D.h"
#include "../MoveStrategy/ModeManager.h"
namespace Logic {
    class Subject {
    public:

    private:
        Vector2D position;
        Move::ModeManager move_manager;
    };

} // Logic

#endif //PROJECTPACMAN_SUBJECT_H
