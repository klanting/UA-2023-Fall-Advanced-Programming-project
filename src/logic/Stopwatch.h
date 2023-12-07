//
// Created by tibov on 25/11/23.
//

#ifndef PROJECTPACMAN_STOPWATCH_H
#define PROJECTPACMAN_STOPWATCH_H
#include <memory>
#include <chrono>
namespace Logic {
    using namespace std::chrono;
    class Stopwatch {
    public:
        static std::shared_ptr<Stopwatch> getInstance();
        double getDeltaTime() const;

        void doTick();

        int getTickIteration() const;

    private:
        Stopwatch();
        inline static std::shared_ptr<Stopwatch> _instance;

        std::chrono::time_point<steady_clock> start_time;
        std::chrono::time_point<steady_clock> end_time;

        int tick_iteration;


    };

} // Logic

#endif //PROJECTPACMAN_STOPWATCH_H
