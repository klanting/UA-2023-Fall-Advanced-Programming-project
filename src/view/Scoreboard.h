//
// Created by tibov on 12/12/23.
//

#ifndef PROJECTPACMAN_SCOREBOARD_H
#define PROJECTPACMAN_SCOREBOARD_H
#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>
namespace View {

    class Scoreboard {
    public:
        static std::shared_ptr<Scoreboard> getInstance();
        void add(unsigned int score);
        ~Scoreboard();
        void render();
    private:
        Scoreboard();

        inline static std::shared_ptr<Scoreboard> _instance;

        std::vector<unsigned int> scores;

    };

} // View

#endif //PROJECTPACMAN_SCOREBOARD_H
