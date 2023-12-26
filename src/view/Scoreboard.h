//
// Created by tibov on 12/12/23.
//

#ifndef PROJECTPACMAN_SCOREBOARD_H
#define PROJECTPACMAN_SCOREBOARD_H
#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>
namespace View {
    /**
     * Design Pattern: Singleton
     * This class maintains a scoreboard of the top 5 Scores
     * */
    class Scoreboard {
    public:
        static std::shared_ptr<Scoreboard> getInstance();
        /**
         * add a score, if in top 5, it will be stored
         * */
        void add(unsigned int score);
        ~Scoreboard();
        /**
         * renders the scores of the scoreboard
         * */
        void render() const;
    private:
        Scoreboard();

        inline static std::shared_ptr<Scoreboard> _instance;

        std::vector<unsigned int> scores;

    };

} // View

#endif //PROJECTPACMAN_SCOREBOARD_H
