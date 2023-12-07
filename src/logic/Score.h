//
// Created by tibov on 03/12/23.
//

#ifndef PROJECTPACMAN_SCORE_H
#define PROJECTPACMAN_SCORE_H
#include "Observer.h"
#include "Subjects/EntityModel.h"
namespace Logic {

    class Score: public Observer{
    public:
        Score(std::weak_ptr<EntityModel> pacman);
        void consume(std::weak_ptr<Subject> other) override;
        void moved() override;
        void died() override;
    private:
        double score;
        double time_till_last;
        std::weak_ptr<Subject> pacman;
    };

} // Logic

#endif //PROJECTPACMAN_SCORE_H
