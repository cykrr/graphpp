#define VKFW_INCLUDE_GL
#include "gui/util.hpp"
#include "gui/window.hpp"
#include "gui/input.hpp"
#include "glad/glad.h"
#include "vkfw/vkfw.hpp"
#include "gui/program.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "gui/camera.hpp"



void onFramebufferResize(
        vkfw::Window const &window,
        size_t width, size_t height
        );

int main()
{
    
    Camera camera;
     
  // Window
    auto instance = vkfw::initUnique();

    vkfw::WindowHints hints;
    hints.clientAPI = vkfw::ClientAPI::eOpenGL;
    hints.openGLProfile = vkfw::OpenGLProfile::eCore;
    hints.contextVersionMajor = 3u;
    hints.contextVersionMinor = 3u;
    hints.focusOnShow = false;

    vkfw::UniqueHandle<vkfw::Window> window;
    
    try {
        window = vkfw::createWindowUnique(800, 600, "pong", hints);
    } catch(std::system_error &e) {
        printf("Exception: %s", e.what());
    }
    window->makeContextCurrent();

    if(!gladLoadGLLoader(
        (GLADloadproc)glfwGetProcAddress)
    ){
        fprintf(stderr, "Error loading GLAD\n");
    }

    // IDK needed for light. Global OpenGL State.
    glEnable(GL_DEPTH_TEST);

    window->callbacks()->on_framebuffer_resize = onFramebufferResize;

    

   

    // Camera

    //// Position & Directions
    glm::vec3 camPos(1.0f),
      camFront(1.0f), camUp(1.0f), camRight(1.0f), camWorldUp(1.0f);

    glm::mat4 camProjection(1.0f), camView(1.0f);

    //// Euler Angles
    float camYaw = -90.0f, camPitch = 0.f;

    //// Options
    float camSpeed = 2.5f, camSensitivity = 0.1f, camZoom = 45.0f;

    //// Set-Up matrices
    camProjection =
      glm::perspective(
		       glm::radians(45.f), // FOV
		       ((float)Window::width/Window::height), // Aspect-Ratio
		       0.1f, 100.f); //zFar, zNear planes

    camView = glm::lookAt(camPos, camPos + camFront, camUp);

    camPos = glm::vec3(0.f, 0.f, 3.f);
    camFront = glm::vec3(0.f, 0.f, -1.f);
    camUp = glm::vec3(0.f, 1.f, 0.f);
    
    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };
    

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    // Lighting
    Program lighting("lighting");
    GLuint lightVao;
    glm::vec3 lightPos(1.0f);
    glGenVertexArrays(1, &lightVao);
    glBindVertexArray(lightVao);
    glVertexAttribPointer(0, 3, GL_FLOAT,
			  GL_FALSE, 6* sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT,
			  GL_FALSE, 6* sizeof(float), (void*)(3*sizeof(float)));

    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    lighting.use();
    lighting.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
    lighting.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
    lighting.setVec3("lightPos", lightPos);

    

    // Light Cube 
    Program lightCube("lightCube");
    GLuint lightCubeVao;
    glGenVertexArrays(1, &lightCubeVao);
    glBindVertexArray(lightCubeVao);

    glVertexAttribPointer(0, 3, GL_FLOAT,
			  GL_FALSE, 6* sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    
    glBindBuffer(GL_ARRAY_BUFFER, VBO); // We use the same VBO. It's a cube as well.
    // (In our case triangle lol)

    // Everything else
    glViewport(0, 0, 800, 600);

    glm::mat4 rotation(1.0f);

    gl::clearColorHex("#202020");
    // Loop !!
    while(!window->shouldClose()) {
      // Time
      Time::now = static_cast<float>(vkfw::getTime());
      Time::dt = Time::now - Time::then;
      Time::then = Time::now;

      Input::process(window);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        rotation = glm::rotate(rotation, (float)(Time::dt*glm::radians(45.f)), glm::vec3(1.f, 0.f, 0.f));

	camProjection = glm::perspective(glm::radians(45.f),
					 ((float)Window::width/Window::height),
					 0.1f, 100.f);


        lightPos = glm::vec3(2 + 8.f * sin(2*Time::now), 
                -0.3f + 6.f*sin(2*Time::now),
                2 + 8.f * cos(2*Time::now));

        camPos = glm::vec3(4.f * sin(Time::now),
                1.f,
                4.f * cos(Time::now));

	lighting.use();
	lighting.setVec3("objectColor", 1.f, 0.5f, 0.31f);
	lighting.setVec3("lightColor", 1.f, 1.f, 1.f);
	lighting.setVec3("lightPos", lightPos);
	lighting.setMat4("View", glm::lookAt(
                                      camPos,
                                      glm::vec3(0.f, 0.f, 0.f),
                                      camUp
					));

	lighting.setMat4("Projection", camProjection);
	lighting.setMat4("World", glm::mat4(1.0f));
	lighting.setMat4("Model", glm::mat4(1.0f));
	glBindVertexArray(lightVao);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	lightCube.use();
	lightCube.setMat4("Projection", camProjection);
	lightCube.setMat4("Model", glm::scale(glm::mat4(1.0f), 
                    glm::vec3(0.2f)) *
	            glm::translate(glm::mat4(1.f), lightPos));
	lightCube.setMat4("View", glm::lookAt(
					      camPos,
					      glm::vec3(0.f, 0.f, 0.f),
					      camUp
					));
	glBindVertexArray(lightCubeVao);
        glDrawArrays(GL_TRIANGLES, 0, 36);
/*
	for(int i = 1; i < 13; i++)
	    glDrawArrays(GL_LINES, i, i+1);
	glDrawArrays(GL_LINES, 14, 15);
        */


	

        vkfw::pollEvents();
        window->swapBuffers();
    }
}

void onFramebufferResize(vkfw::Window const &, size_t width, size_t height) {
  printf("Resized framebuffer: %zdx%zd\n", width, height);
  glViewport(0, 0, static_cast<GLsizei>(width), static_cast<GLsizei>(height));
  Window::width = width;
  Window::height = height;
}
