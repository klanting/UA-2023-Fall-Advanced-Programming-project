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
    class Observer;

    /**
     * Abstract class to be able to add observers to entities
     * */
    class Subject {
    public:
        Subject() = default;

        void addObserver(std::shared_ptr<Observer> observer);
        virtual ~Subject();
    protected:
        std::vector<std::shared_ptr<Observer>> observers;


    };

} // Logic

#endif //PROJECTPACMAN_SUBJECT_H
