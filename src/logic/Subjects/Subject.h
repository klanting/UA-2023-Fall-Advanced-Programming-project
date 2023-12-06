//
// Created by tibov on 25/11/23.
//

#ifndef PROJECTPACMAN_SUBJECT_H
#define PROJECTPACMAN_SUBJECT_H
#include "../Vector2D.h"
#include "../MoveStrategy/ModeManager.h"
#include <functional>
#include <memory>
namespace Logic {
    class Subject {
    public:
        Subject() = default;
        virtual void move() = 0;
        virtual void moveConfirm() = 0;
        virtual bool isConsumable() = 0;

        virtual const Vector2D &getPosition() const = 0;
        virtual const Vector2D &getSize() const = 0;
        virtual std::pair<bool, std::pair<Vector2D, Vector2D>> collide(std::weak_ptr<Subject> other) = 0;
        virtual std::shared_ptr<Move::ModeManager> getMoveManager() = 0;
        virtual void handleImpassable(std::weak_ptr<Subject> other, bool fix = false) = 0;
        virtual bool handleDead(std::vector<std::shared_ptr<Subject>> others) = 0;
        virtual void changeMode() = 0;
        virtual ~Subject();

        bool debug_green = false;
    protected:


    };

} // Logic

#endif //PROJECTPACMAN_SUBJECT_H
