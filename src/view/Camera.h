//
// Created by tibov on 02/12/23.
//

#ifndef PROJECTPACMAN_CAMERA_H
#define PROJECTPACMAN_CAMERA_H
#include <memory>
#include "../logic/Vector2D.h"
#include "RenderWindowSingleton.h"
namespace View {

    /**
     * Design Pattern: Singleton
     * This Class will convert relative positions to Absolute Pixel positions
     * */
    class Camera {
    public:
        static std::shared_ptr<Camera> getInstance();
        /**
         * convert given relative position and size to absolute
         * */
        [[nodiscard]] std::pair<Logic::Vector2D<>, Logic::Vector2D<>> toPixels(const Logic::Vector2D<>& position, const Logic::Vector2D<>& size) const;
    private:
        Camera(unsigned int width, unsigned int height);

        inline static std::shared_ptr<Camera> _instance;

        unsigned int width;
        unsigned int height;
    };

} // View

#endif //PROJECTPACMAN_CAMERA_H
