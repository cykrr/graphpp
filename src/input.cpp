#include "gui/input.hpp"
namespace Input {
    void keyboard(vkfw::UniqueHandle<vkfw::Window> &window) {
        Container *container = static_cast<Container*>(window->getUserPointer());
        if(window->getKey(vkfw::Key::eQ)) 
            window->setShouldClose(true);
        if(window->getKey(vkfw::Key::eW)){
            container->camera->processInput(Camera::Direction::Forward);
        }
        if(window->getKey(vkfw::Key::eS))
            container->camera->processInput(Camera::Direction::Backwards);
        if(window->getKey(vkfw::Key::eA))
            container->camera->processInput(Camera::Direction::Left);
        if(window->getKey(vkfw::Key::eD))
            container->camera->processInput(Camera::Direction::Right);
    }

        int Input::Mouse::xoffset = 0,
        Input::Mouse::yoffset = 0;

    void mouse(const vkfw::Window &window, double x, double y) {
        Camera *camera = static_cast<Container*>(window.getUserPointer())->camera;


        if(camera->firstTime) {
            camera->lastX = x;
            camera->lastY = y;
            camera->firstTime = false;
        }

        Mouse::xoffset = x - camera->lastX;
        Mouse::yoffset = y - camera->lastY;
        camera->lastX = x;
        camera->lastY = y;
        camera->mouse(Mouse::xoffset, -Mouse::yoffset);
        
    }

}
