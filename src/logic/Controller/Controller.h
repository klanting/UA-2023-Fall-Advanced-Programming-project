//
// Created by tibov on 25/11/23.
//

#ifndef PROJECTPACMAN_CONTROLLER_H
#define PROJECTPACMAN_CONTROLLER_H
#include <memory>
#include <vector>
#include "../Vector2D.h"
namespace Controller {

    class ControllerObserver;

    using namespace Logic;
    class Controller {
    public:
        Controller() = default;
        void addObserver(std::shared_ptr<ControllerObserver> controller_observer);

        const Vector2D &getDataVector() const;

    protected:
        std::vector<std::shared_ptr<ControllerObserver>> observers;
        Vector2D data_vector;
    };

} // Controller

#endif //PROJECTPACMAN_CONTROLLER_H
