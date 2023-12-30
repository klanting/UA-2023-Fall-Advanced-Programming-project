//
// Created by tibov on 30/12/23.
//

#ifndef PROJECTPACMAN_HIGHSCORE_H
#define PROJECTPACMAN_HIGHSCORE_H
#include <vector>
#include <memory>
#include <fstream>
#include <algorithm>
namespace Logic {

    /**
     * Design Pattern: Singleton
     * This class maintains a the top 5 scores
     * */
    class HighScore {
    public:
        static std::shared_ptr<HighScore> getInstance();
        /**
         * add a score, if in top 5, it will be stored
         * */
        void add(unsigned int score);
        ~HighScore();

        [[nodiscard]] std::vector<unsigned int> getScores() const;


    private:
        HighScore();

        inline static std::shared_ptr<HighScore> _instance;

        std::vector<unsigned int> scores;

    };

} // Logic

#endif //PROJECTPACMAN_HIGHSCORE_H
