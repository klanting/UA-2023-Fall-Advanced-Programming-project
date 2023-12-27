//
// Created by tibov on 25/12/23.
//

#ifndef PROJECTPACMAN_TYPERULEMANAGER_H
#define PROJECTPACMAN_TYPERULEMANAGER_H
#include "TypeRule.h"
#include <map>
#include <string>
#include "../../Vector2D.h"
#include "Matrix.h"
#include <fstream>
#include "WFCReader.h"

    namespace Logic::WFC {

        class TypeRuleManager {
        public:
            TypeRuleManager(const std::string& file_path, const std::vector<Vector2D<int>>& directions);
            std::set<int> getOptions(int type, int direction_index);

            int getCharAmount();

            [[nodiscard]] int getWallCount() const;

        private:
            std::map<int, TypeRule> type_map;
            int wall_count;

        };

    } // WFC
// Logic

#endif //PROJECTPACMAN_TYPERULEMANAGER_H
