//
// Created by tibov on 25/11/23.
//

#ifndef PROJECTPACMAN_SUBJECT_H
#define PROJECTPACMAN_SUBJECT_H
#include "../Vector2D.h"
#include "../MoveStrategy/ModeManager.h"
#include <functional>
namespace Logic {
    class Subject {
    public:
        Subject(const Vector2D& position, std::unique_ptr<Move::Mode> mode);

    protected:
        Vector2D position;
        Move::ModeManager move_manager;
    };

} // Logic

#endif //PROJECTPACMAN_SUBJECT_H
