//
// Created by tibov on 25/11/23.
//

#ifndef PROJECTPACMAN_RANDOM_H
#define PROJECTPACMAN_RANDOM_H
#include <memory>
#include <random>
namespace Logic {

    class Random {
    public:
        static std::shared_ptr<Random> getInstance();

        double getRandom();
        int getRandomIndex(int a, int b);
    private:
        Random();
        inline static std::shared_ptr<Random> _instance;
        std::unique_ptr<std::mt19937> generator;

    };

} // Logic

#endif //PROJECTPACMAN_RANDOM_H
