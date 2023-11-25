//
// Created by tibov on 25/11/23.
//

#ifndef PROJECTPACMAN_STOPWATCH_H
#define PROJECTPACMAN_STOPWATCH_H
#include <memory>
namespace Logic {

    class Stopwatch {
    public:
        static std::shared_ptr<Stopwatch> getInstance();

    private:
        Stopwatch();
        inline static std::shared_ptr<Stopwatch> _instance;

    };

} // Logic

#endif //PROJECTPACMAN_STOPWATCH_H
