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
     * This class will be te base class for EntityModel
     */
    class Subject {
    public:
        /**
         * Constructor for Subject is a default constructor
         */
        Subject() = default;

        /**
         * Destructor for Subject is a default destructor
         */
        virtual ~Subject() = default;

        /**
         * function to add observers to a subject
         */
        void addObserver(const std::shared_ptr<Observer>& observer);

    protected:
        /**
         * vector of all the observers that we will pass an event to
         **/
        std::vector<std::shared_ptr<Observer>> observers;


    };

} // Logic

#endif //PROJECTPACMAN_SUBJECT_H
