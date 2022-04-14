#ifndef UTIL_H
#define UTIL_H
#include <string>
#include "glad/glad.h"
#include "vkfw/vkfw.hpp"
namespace gl {
    void clearColorHex(std::string hex);
}

namespace Time {
  extern float dt;
  extern double now;
  extern double then;
  void update();
}

#endif
