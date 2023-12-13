//
// Created by tibov on 13/12/23.
//

#include <iostream>
#include "IntersectionHandler.h"

namespace Logic {

    IntersectionHandler::IntersectionHandler(const std::vector<std::shared_ptr<EntityModel>> &not_passable,
                                             std::shared_ptr<EntityModel> pacman): not_passable{not_passable}, pacman{pacman} {

    }

    void IntersectionHandler::linkIntersections(std::shared_ptr<EntityModel> entity) {
        Vector2D dir = entity->getDirection();
        Vector2D center = entity->getPosition() + entity->getSize()*0.5;

        Vector2D i_dir = dir.rotate(-1*M_PI/2.0);

        Vector2D low_bound = i_dir+dir;
        Vector2D high_bound = i_dir+dir.getOpposed();

        Vector2D e_low = center + entity->getSize()*(i_dir+dir)*0.5;
        Vector2D e_high = center + entity->getSize()*(i_dir+dir.getOpposed())*0.5;

        auto iti = intersection_center.find(entity);
        if (iti != intersection_center.end()){
            if (center.getDistance(iti->second) < 0.12){
                return;
            }
        }


        bool just_changed = false;
        auto it = intersection_map.find(entity);
        if (it != intersection_map.end() && !(std::get<0>(it->second)== Vector2D{10, 10} || std::get<1>(it->second) == Vector2D{10,10})){
            Vector2D latest_low = std::get<0>(it->second);
            Vector2D latest_high = std::get<1>(it->second);
            //std::cout << "a " << e_low[0] << " " << e_low[1] << std::endl;
            if (low_bound.getAngle(latest_low-e_low) <= M_PI/4.0){
                return;
            }

            //caclulater high again
            Vector2D best_high = Vector2D{10, 10};
            for (auto p: not_passable){
                Vector2D p_center = p->getPosition() + p->getSize()*0.5;
                if ((center-p_center).projection(i_dir).getLength() > (entity->getSize().getLength()+p->getSize().getLength())/2.0+ 0.02){
                    continue;
                }
                Vector2D high = p_center + p->getSize()*(i_dir.getOpposed()+dir)*0.5;

                if (high.getDistance(e_high) < best_high.getDistance(e_high) && high_bound.getAngle(high-e_high) <= M_PI/4.0*1.1){
                    best_high = high;
                }


            }


            bool intersect = latest_low.getDistance(best_high) >= entity->getSize()[0] && latest_low.getDistance(best_high) < entity->getSize()[0]*2;

            if (intersect && !std::get<2>(it->second)){
                just_changed = true;

                double angle = (best_high-center).getAngle((latest_low-center));
                if (angle >= M_PI/2*0.9 && angle <= M_PI){
                    Vector2D to = entity->getPosition() - entity->getPosition()*(+dir) + ((latest_low+best_high)*0.5- entity->getSize()*0.5)*(+dir);
                    Vector2D to2 = entity->getPosition() + (latest_low - e_low)*(+dir)*1.1;
                    entity->getMoveManager()->makeDirection(pacman->getPosition(), {i_dir, i_dir.getOpposed(), dir});

                    if (entity->getDirection().getAngle(dir) > 0.1){
                        entity->setPosition(to2);

                    }
                    std::cout << "to 1 " << to[0] << " " << to[1] << std::endl;
                    std::cout << "to 2 " << to2[0] << " " << to2[1] << std::endl;

                    std::cout << "changed from " << dir[0] << " " << dir[1] << std::endl;
                    std::cout << "changed to " << entity->getMoveManager()->getDirection()[0] << " " << entity->getMoveManager()->getDirection()[1] << std::endl;
                    std::cout << "center count " << intersection_center.size() << std::endl;
                    if (iti != intersection_center.end()){
                        std::cout << "to center " << iti->second.getDistance(center) << std::endl;
                    }

                    setCenter(entity, center);
                    std::cout << "center count2 " << intersection_center.size() << std::endl;

                    //recalibrate
                    dir = entity->getDirection();
                    center = entity->getPosition() + entity->getSize()*0.5;

                    i_dir = dir.rotate(-1*M_PI/2.0);

                    low_bound = i_dir+dir;
                    high_bound = i_dir+dir.getOpposed();

                    e_low = center + entity->getSize()*(i_dir+dir)*0.5;
                    e_high = center + entity->getSize()*(i_dir+dir.getOpposed())*0.5;


                }
            }

        }

        Vector2D best_low = Vector2D{10, 10};
        std::weak_ptr<EntityModel> best_model_low;

        Vector2D best_high = Vector2D{10, 10};
        std::weak_ptr<EntityModel> best_model_high;
        //lowest low
        for (auto p: not_passable){
            Vector2D p_center = p->getPosition() + p->getSize()*0.5;
            if ((center-p_center).projection(i_dir).getLength() > (entity->getSize().getLength()+p->getSize().getLength())/2.0+ 0.02){
                continue;
            }

            //std::cout << "a" << std::endl;

            Vector2D low = p_center + p->getSize()*(i_dir.getOpposed()+dir.getOpposed())*0.5;
            Vector2D high = p_center + p->getSize()*(i_dir.getOpposed()+dir)*0.5;

            if (low.getDistance(e_low) < best_low.getDistance(e_low) && low_bound.getAngle(low-e_low) <= M_PI/4.0*1.1){
                best_low = low;
                best_model_low = p;
            }

            if (high.getDistance(e_high) < best_high.getDistance(e_high) && high_bound.getAngle(high-e_high) <= M_PI/4.0*1.1){
                best_high = high;
                best_model_high = p;
            }


        }

        if (!best_model_low.expired()){
            best_model_low.lock()->debug_green = true;
        }

        if (best_model_low.lock() == best_model_high.lock()){
            if (it != intersection_map.end()){
                intersection_map.erase(it);
            }

            return;
        }


        if (it == intersection_map.end()){
            intersection_map.insert({entity, std::make_tuple(best_low, best_high, just_changed)});
        }else{
            it->second = std::make_tuple(best_low, best_high, just_changed);
        }

    }

    void IntersectionHandler::clearIntersection(std::shared_ptr<EntityModel> entity) {
        auto it = intersection_center.find(entity);
        if (it != intersection_center.end()){
            intersection_center.erase(it);
        }

    }

    bool IntersectionHandler::inLastIntersection(std::shared_ptr<EntityModel> entity) {
        auto it = intersection_center.find(entity);
        if (it != intersection_center.end()){
            Vector2D center = entity->getPosition() + entity->getSize()*0.5;
            if (center.getDistance(it->second) < 0.12){
                return true;
            }
        }
        return false;
    }

    void IntersectionHandler::setCenter(std::shared_ptr<EntityModel> entity, const Vector2D &v) {
        auto it = intersection_center.find(entity);
        if (it != intersection_center.end()){
            it->second = v;

        }else{
            intersection_center.insert({entity, v});
        }

    }
} // Logic