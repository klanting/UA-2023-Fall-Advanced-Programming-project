//
// Created by tibov on 13/12/23.
//

#ifndef PROJECTPACMAN_INTERSECTIONHANDLER_H
#define PROJECTPACMAN_INTERSECTIONHANDLER_H

#include "Subjects/EntityModel.h"
#include "vector"
#include "map"
namespace Logic {

    class IntersectionHandler {
    public:
        IntersectionHandler(const std::vector<std::shared_ptr<EntityModel>>& not_passable, std::shared_ptr<EntityModel> pacman);
        void linkIntersections(std::shared_ptr<EntityModel> entity);
        void clearIntersection(std::shared_ptr<EntityModel> entity);
        bool inLastIntersection(std::shared_ptr<EntityModel> entity);
        void setCenter(std::shared_ptr<EntityModel> entity, const Vector2D& v);
    private:
        std::vector<std::shared_ptr<EntityModel>> not_passable;
        std::shared_ptr<EntityModel> pacman;

        std::map<std::shared_ptr<EntityModel>, std::tuple<Vector2D, Vector2D, bool>> intersection_map;
        std::map<std::shared_ptr<EntityModel>, Vector2D> intersection_center;

    };

} // Logic

#endif //PROJECTPACMAN_INTERSECTIONHANDLER_H
