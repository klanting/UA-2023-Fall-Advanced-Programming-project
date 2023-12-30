//
// Created by tibov on 03/12/23.
//

#ifndef PROJECTPACMAN_SCORE_H
#define PROJECTPACMAN_SCORE_H
#include "Observer.h"
#include "Subjects/EntityModel.h"
#include "HighScore.h"
namespace Logic {

    class Score: public Observer{
    public:
        /**
         * initialize Score class
         * */
        Score();

        /**
         * add EntityModel as observed
         * */
        void addObserved(const std::weak_ptr<EntityModel>& pacman_ptr);
        void consume(std::weak_ptr<EntityModel> other) override;
        void moved() override;
        void died() override;
        [[nodiscard]] int getScore() const;
        void finishedLvl();
        ~Score() override = default;

        /**
         * Score needs to decrease over time, this function will check whether to decrease the score
         * */
        void checkDecrease();
    private:
        double score;
        double time_till_last;
        double decrease_remaining = 1.0;
        std::weak_ptr<Subject> pacman;
    };

} // Logic

#endif //PROJECTPACMAN_SCORE_H
