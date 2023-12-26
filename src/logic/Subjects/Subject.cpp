

#include "Subject.h"
#include "../Observer.h"
namespace Logic {

    void Subject::addObserver(const std::shared_ptr<Observer>& observer) {
        observers.push_back(observer);

    }

} // Logic