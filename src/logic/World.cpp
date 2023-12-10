//
// Created by tibov on 25/11/23.
//

#include "World.h"
#include "fstream"
#include "iostream"
#include "functional"

namespace Logic {

    World::World(std::shared_ptr<AbstractFactory> factory, std::shared_ptr<Score> score) {
        lives = 3;

        std::shared_ptr<EntityModel> s = factory->createPacman(Vector2D{0, -0.0725}, score);
        entities.push_back(s);
        pacman = s;

        std::vector<std::pair<Vector2D, Vector2D>> wall_positions = {};
        std::fstream f("maps/wall_positions2.txt");

        std::string buffer;
        std::vector<double> doubles;
        while (!f.eof()){

            char c = f.get();
            if (c == ' '){
                doubles.push_back(std::stod(buffer));
                buffer = "";
            }else if (c == '\n'){
                doubles.push_back(std::stod(buffer));
                wall_positions.push_back({Vector2D{doubles[0], doubles[1]}, Vector2D{doubles[2], doubles[3]}});
                doubles = {};
                buffer = "";
            }else{
                buffer += c;
            }
        }


        for (auto w: wall_positions){
            s = factory->createWall(w.first, w.second);
            entities.push_back(s);
            not_passable.push_back(s);
        }

        for (auto w: {Vector2D{-0.885, -0.835}, Vector2D{0.815, -0.035}}){
            s = factory->createFruit(w);
            entities.push_back(s);
        }

        Vector2D ghost_spawn = Vector2D{0-0.07, -0.5};
        for (int i=0; i<1; i++){
            double delay = 0;

            if (i == 1){
                delay = 1;
            }
            if (i>= 2){
                delay = 5.0 * (i-1);
            }

            s = factory->createGhost(ghost_spawn, delay, i);
            s->getMoveManager()->makeDirection(pacman->getPosition()-s->getPosition(), {Vector2D{0, -1}});
            entities.push_back(s);

            linkIntersections(s);
            debug_ghost = s;
        }

        std::vector<std::shared_ptr<EntityModel>> coin_buffer;
        for (int i=-9; i<9; i++){
            for (int j=-9; j<0; j++){
                s = factory->createCoin(Vector2D{i/10.0+0.025, j/10.0+0.0751});

                if (i >= -2 && i <= 1 && j == -5){
                    continue;
                }
                if (i >= -1 && i <= 0 && j == -6){
                    continue;
                }

                bool found = false;
                for (auto np: not_passable){
                    Vector2D np_pos = np->getPosition();
                    Vector2D np_pos2 = np->getPosition()+np->getSize();
                    if (s->getPosition()[0] >= np_pos[0] && s->getPosition()[0] < np_pos2[0] && s->getPosition()[1] >= np_pos[1] && s->getPosition()[1] < np_pos2[1]){
                        found = true;
                    }
                }

                if (!found){
                    coin_buffer.push_back(s);
                }
            }
        }

        entities.insert(entities.begin(), coin_buffer.begin(), coin_buffer.end());


    }

    std::vector<std::weak_ptr<EntityModel>> World::checkCollision(std::shared_ptr<EntityModel> s, bool inpassable) {
        std::vector<std::weak_ptr<EntityModel>> hits;

        auto to_check = entities;
        if (inpassable){
            to_check = not_passable;
        }

        for (std::shared_ptr<EntityModel> other: to_check){
            if (s == other){
                continue;
            }

            auto p = s->collide(other);
            if (p.first){
                hits.push_back(other);
            }

        }
        return hits;
    }

    bool World::doTick() {
        using ColHandle = void (World::*)(std::shared_ptr<EntityModel>, std::weak_ptr<EntityModel>, std::vector<std::weak_ptr<EntityModel>>&);
        std::vector<std::weak_ptr<EntityModel>> to_be_removed = {};

        for (auto& e: entities){
            e->move();
            handleInPassable(e);

            ColHandle func;
            if (e == pacman){
                func = &World::handleActionsPacman;
            }else{
                func = &World::handleActions;
            }

            std::vector<std::weak_ptr<EntityModel>> hits = checkCollision(e);
            for (auto hit: hits){
                (this->*func)(e, hit, to_be_removed);
            }


        }

        linkIntersections(debug_ghost);

        for (auto e: to_be_removed){
            auto it = std::find(entities.begin(), entities.end(), e.lock());
            entities.erase(it);
        }
        return lives > 0;

    }

    void World::handleInPassable(std::shared_ptr<EntityModel> e) {
        bool hit_wall = false;
        bool fix = true;
        bool collision = true;
        while (collision){
            std::vector<std::weak_ptr<EntityModel>> np;
            for (int i = 0; i<2;i++){
                std::vector<std::weak_ptr<EntityModel>> hits = checkCollision(e, true);
                if (hits.empty()){
                    collision = false;
                    break;
                }


                for (auto hit: hits){
                    e->handleImpassable(hit, fix &&  hits.size() < 3);
                    hit_wall = true;
                    np.push_back(hit);

                }
            }

            fix = false;

        }

        if (hit_wall){

            std::vector<Vector2D> option_directions = {Vector2D{0,1}, Vector2D{0,-1}, Vector2D{1,0}, Vector2D{-1,0}};
            auto it = std::find(option_directions.begin(), option_directions.end(), e->getMoveManager()->getDirection());
            if (it != option_directions.end()){
                option_directions.erase(it);
            }
            auto it2 = std::find(option_directions.begin(), option_directions.end(), e->getMoveManager()->getDirection()*-1);
            if (it2 != option_directions.end()){
                option_directions.erase(it2);
            }

            std::cout << "col" << std::endl;
            e->getMoveManager()->makeDirection(pacman->getPosition()-e->getPosition(), option_directions);

            auto iti = intersection_map.find(e);
            if (iti != intersection_map.end()){

                intersection_map.erase(iti);
            }

        }

    }

    void World::handleActionsPacman(std::shared_ptr<EntityModel> e, std::weak_ptr<EntityModel> hit,
                                    std::vector<std::weak_ptr<EntityModel>> &to_be_removed) {

        if (hit.lock()->isConsumable()){
            e->consume(hit);
            if (hit.lock()->handleDead(entities)){
                to_be_removed.push_back(hit);
            }

        } else{
            e->handleDead(entities);
            lives -= 1;

            if (lives == 0){
                std::cout << "game over" << std::endl;
            }
        }

    }

    void World::handleActions(std::shared_ptr<EntityModel> e, std::weak_ptr<EntityModel> hit,
                              std::vector<std::weak_ptr<EntityModel>> &to_be_removed) {
        //make sure only ghosts do this
        if (hit.lock() == pacman){
            handleActionsPacman(hit.lock(), e, to_be_removed);
            /*
            e->consume(hit);
            if (hit.lock()->handleDead(entities)){
                to_be_removed.push_back(hit);
            }*/

        }

    }

    int World::getLives() const {
        return lives;
    }

    void World::linkIntersections(std::shared_ptr<EntityModel> entity) {

        Vector2D dir = entity->getDirection();
        Vector2D center = entity->getPosition() + entity->getSize()*0.5;

        Vector2D i_dir = dir.rotate(-1*M_PI/2.0);

        Vector2D low_bound = i_dir+dir;
        Vector2D high_bound = i_dir+dir.getOpposed();

        Vector2D l_low = entity->getLastPosition() + entity->getSize()*0.5 + entity->getSize()*(i_dir+dir)*0.5;

        Vector2D e_low = center + entity->getSize()*(i_dir+dir)*0.5;
        Vector2D e_high = center + entity->getSize()*(i_dir+dir.getOpposed())*0.5;


        bool just_changed = false;
        auto it = intersection_map.find(entity);
        if (it != intersection_map.end() && !(std::get<0>(it->second)== Vector2D{10, 10} || std::get<1>(it->second) == Vector2D{10,10})){
            Vector2D latest_low = std::get<0>(it->second);
            Vector2D latest_high = std::get<1>(it->second);
            //std::cout << "a " << e_low[0] << " " << e_low[1] << std::endl;
            if (low_bound.getAngle(latest_low-e_low) <= M_PI/4.0){
                return;
            }

            /*
            bool intersect = latest_low.getDistance(latest_high) >= entity->getSize()[0];
            //bool intersect2 = (latest_low-e_low).getAngle((latest_high-e_high)) >= M_PI/2.0*0.9;

            auto iti = intersection_center.find(entity);
            if (iti != intersection_center.end()){
                if (center.getDistance(iti->second) < 0.12){
                    return;
                }
            }




            if (intersect && !std::get<2>(it->second)){
                just_changed = true;
                std::cout << "r2" << std::endl;
                std::cout << "c " << center[0] << " " <<center[1] << std::endl;

                //Vector2D cross_line = latest_low.projection(dir);
                //std::cout << "x " << cross_line[0] << " " <<cross_line[1] << std::endl;


                //here pseudo col det

                //entity->setPosition(entity->getPosition() + (latest_low-e_low).projection(dir)*1.01);
                //std::cout << "t " << (entity->getPosition() + (latest_low-e_low)*dir*1.01)[0] << " " <<(entity->getPosition() + (latest_low-e_low)*dir*1.01)[1] << std::endl;

                //entity->getMoveManager()->makeDirection(pacman->getPosition(), {Vector2D{0, 0}});
                //entity->setPosition(entity->getLastPosition());

                //entity->setPosition(entity->getLastPosition());

                //entity->setPosition(entity->getPosition() + dir.getOpposed()*latest_low.getDistance(e_low)*1.1);
                std::cout << "t " << (dir.getOpposed()*latest_low.getDistance(e_low)*1.1)[0] << " " <<(dir.getOpposed()*latest_low.getDistance(e_low)*1.1)[1] << std::endl;
                //entity->getMoveManager()->makeDirection(pacman->getPosition(), {i_dir, i_dir.getOpposed(), dir});
                entity->getMoveManager()->makeDirection(pacman->getPosition(), {Vector2D{0, 0}});



                if (iti == intersection_center.end()){
                    intersection_center.insert({entity, center});
                }else{
                    iti->second = center;
                }

            }*/




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
        if (!best_model_high.expired()){
            best_model_high.lock()->debug_green = true;
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
        //intersection_map.insert({entity, std::make_pair(best_low, best_high)});
        //intersection_map[entity] = std::make_pair(best_low, best_high);

    }


} // Logic