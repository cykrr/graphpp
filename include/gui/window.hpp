#include "vkfw/vkfw.hpp"
#include "glm/glm.hpp"

#include "gui/camera.hpp"
#define FIXED_WIDTH 800
#define FIXED_HEIGHT 600
namespace Window { 
  vkfw::UniqueHandle<vkfw::Window> init();
  static int width = FIXED_WIDTH, height = FIXED_HEIGHT;

  
}

class Container {
    Window *window;
    Camera *camera;
};
