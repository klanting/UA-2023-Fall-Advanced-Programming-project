//
// Created by tibov on 02/12/23.
//

#include "Camera.h"

namespace View {
    Camera::Camera(unsigned int width, unsigned int height): width{width}, height{height} {

    }

    std::shared_ptr<Camera> Camera::getInstance() {
        if (!_instance){
            _instance = std::shared_ptr<Camera>(new Camera{1000, 1000});
        }
        return _instance;
    }

    std::pair<Logic::Vector2D, Logic::Vector2D>
    Camera::toPixels(const Logic::Vector2D &position, const Logic::Vector2D &size) const{
        //positions are between (-1, -1) and (1,1)
        Logic::Vector2D scale_vector = Logic::Vector2D{(double) width, (double)  height};
        Logic::Vector2D pixelPosition = (position+Logic::Vector2D{1,1})*0.5*scale_vector;
        Logic::Vector2D pixelSize = size*0.5*scale_vector;

        return std::make_pair(pixelPosition, pixelSize);
    }


} // View