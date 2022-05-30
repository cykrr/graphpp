const float near_plane = 0.1f;
const float far_plane = 100.0f;
#define VKFW_INCLUDE_GL

#include "gui/camera.hpp"
#include "gui/window.hpp"
#include "gui/program.hpp"


#include "glad/glad.h"
#include "vkfw/vkfw.hpp"

#include "glm/gtc/matrix_transform.hpp"

#include "gui/plane.hpp"
#include "gui/util.hpp"
#include "gui/input.hpp"


void onFramebufferResize(
        vkfw::Window const &window,
        unsigned long width, unsigned long height
        );


int main()
{
    // Window
    Container container;
    mWindow wm;
    Camera cam;

    container.wm = &wm;
    container.camera = &cam;

    wm.window->callbacks()->
        on_framebuffer_resize = onFramebufferResize;

    wm.window->callbacks()->
        on_cursor_move = Input::mouse;

    wm.window->set<vkfw::InputMode::eCursor>
        (vkfw::CursorMode::eDisabled);

    wm.window->setUserPointer(&container);


    Plane *plane = new Plane();
    container.programs.push_back(plane->program);

    /*
       GLuint VBO;
       glGenBuffers(1, &VBO);
       glBindBuffer(GL_ARRAY_BUFFER, VBO);
       */


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
    /*
       Program lighting("lighting");
       container.addProgram(&lighting);

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
    container.addProgram(&lightCube);

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

*/
    gl::clearColorHex("#202020");

    // Loop !!
    while(!wm.window->shouldClose()) {
        // Time
        Time::update();
        cam.look();

        Input::keyboard(wm.window);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        /*
           rotation = glm::rotate(rotation, (float)(Time::dt*glm::radians(45.f)), glm::vec3(1.f, 0.f, 0.f));

           lightPos = glm::vec3(2 + 8.f * sin(2*Time::now), 
           -0.3f + 6.f*sin(2*Time::now),
           2 + 8.f * cos(2*Time::now));



*/

        /*
           plane->program->use();
           glBindVertexArray(plane->Vao);
           glBindBuffer(GL_ARRAY_BUFFER, plane->Vbo);
           plane->program->setMat4("View", camera.view);
           plane->program->setMat4("Projection", camera.projection);
           glBufferSubData(GL_ARRAY_BUFFER, 0, 18*sizeof(float), plane->vertices);
           */
        plane->program->use();
        plane->program->setMat4("View", cam.view);

        plane->draw();
        //        glDrawArrays(GL_TRIANGLES, 0, 6);

        /*

           lighting.use();
           lighting.setVec3("objectColor", 1.f, 0.5f, 0.31f);
           lighting.setVec3("lightColor", 1.f, 1.f, 1.f);
           lighting.setVec3("lightPos", lightPos);

           lighting.setMat4("View", camera.view);

           lighting.setMat4("Projection", camera.projection);

           lighting.setMat4("World", glm::mat4(1.0f));
           lighting.setMat4("Model", glm::mat4(1.0f));
           glBindVertexArray(lightVao);
           */
        //	glDrawArrays(GL_TRIANGLES, 0, 36);


        /*
           lightCube.use();

           lightCube.setMat4("Model", glm::scale(glm::mat4(1.0f), 
           glm::vec3(0.2f)) *
           glm::translate(glm::mat4(1.f), lightPos));

           lightCube.setMat4("View", camera.view);
           glBindVertexArray(lightCubeVao);
        //        glDrawArrays(GL_TRIANGLES, 0, 36);
        for(int i = 1; i < 13; i++)
        glDrawArrays(GL_LINES, i, i+1);
        glDrawArrays(GL_LINES, 14, 15);

*/
        wm.window->swapBuffers();
        vkfw::pollEvents();
    }
}

void onFramebufferResize(vkfw::Window const &window, 
        unsigned long width, unsigned long height) {

    printf("Resized framebuffer: %zdx%zd\n", width, height);
    Container *container = static_cast<Container *>
        (window.getUserPointer());

    Camera *camera = container->camera;

    glViewport(0, 0, 
            static_cast<GLsizei>(width), 
            static_cast<GLsizei>(height));

    camera->resizeCallback(width, height);
    for(Program *program : container->programs) {
        program->use();
        program->setMat4("Projection", camera->projection);
    }

    Window::width = width;
    Window::height = height;
}
