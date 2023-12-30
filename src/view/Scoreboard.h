//
// Created by tibov on 12/12/23.
//

#ifndef PROJECTPACMAN_SCOREBOARD_H
#define PROJECTPACMAN_SCOREBOARD_H
#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>
#include "UIObjects/UIObject.h"
#include "../logic/HighScore.h"
namespace View {
    /**
     * This class renders a scoreboard of the top 5 Scores
     * */
    class Scoreboard: public UIObject{
    public:
        Scoreboard();

        ~Scoreboard() override = default;
        /**
         * renders the scores of the scoreboard
         * */
        void render() const override;
    private:

    };

} // View

#endif //PROJECTPACMAN_SCOREBOARD_H
