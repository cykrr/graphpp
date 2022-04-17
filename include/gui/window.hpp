#ifndef WINDOW_H
#define WINDOW_H
#include "vkfw/vkfw.hpp"
#include "glm/glm.hpp"

#include "gui/camera.hpp"
#include "gui/program.hpp"
#define FIXED_WIDTH 800
#define FIXED_HEIGHT 600
namespace Window { 
  vkfw::UniqueHandle<vkfw::Window> init();
  static int width = FIXED_WIDTH, height = FIXED_HEIGHT;

  
}


class mWindow {
public:
    mWindow();

    vkfw::UniqueHandle<vkfw::Window> window;
};

class Container {
    public:
        Camera *camera;
        mWindow *wm;
        std::vector<Program *> programs;
        void addProgram(Program *program);
};

#endif
