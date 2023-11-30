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
        virtual void move() = 0;
        virtual void calculateDirection(const Vector2D& to_pacman, const std::vector<Vector2D>& options) = 0;

        const Vector2D &getPosition() const;

        const Vector2D &getSize() const;

    protected:
        Vector2D position;
        Vector2D size;
        Move::ModeManager move_manager;
    };

} // Logic

#endif //PROJECTPACMAN_SUBJECT_H
