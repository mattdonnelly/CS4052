//
//  main.cpp
//  Assignment 4
//
//  Created by Matt Donnelly on 09/11/2014.
//  Copyright (c) 2014 Matt Donnelly. All rights reserved.
//

#define STB_IMAGE_IMPLEMENTATION
#define GLM_FORCE_RADIANS

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <math.h>

#include "GLCamera.h"
#include "GLBuffer.h"
#include "GLVertexArray.h"
#include "GLShader.h"
#include "GLTexture.h"
#include "GLProgram.h"
#include "stb_image.h"
#include "obj_parser.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

#define RETINA 1

#if RETINA
    #define GL_WIDTH (WINDOW_WIDTH  * 2)
    #define GL_HEIGHT (WINDOW_HEIGHT  * 2)
#else
    #define GLWIDTH WINDOW_WIDTH
    #define GL_HEIGHT WINDOW_HEIGHT
#endif

#if RETINA
    #define MOUSE_SENSITIVITY 0.0056f
#else
    #define MOUSE_SENSITIVITY 0.02f
#endif

static GLCamera camera;
static bool windowIsActive = true;

bool positionInWindow(GLFWwindow *window, double mouseX, double mouseY) {
    int windowX, windowY;
    glfwGetWindowPos(window, &windowX, &windowY);

    return (mouseX > 0 && mouseX < WINDOW_WIDTH) && (mouseY > 0 && mouseY < WINDOW_HEIGHT);
}

void handleCursorPosition(GLFWwindow *window, double xpos, double ypos) {
    static double last_xpos = xpos;
    static double last_ypos = ypos;
    
    if (windowIsActive && positionInWindow(window, xpos, ypos)) {
        double xpos_delta;
        double ypos_delta;

        xpos_delta = (last_xpos - xpos) * MOUSE_SENSITIVITY;
        ypos_delta = (last_ypos - ypos) * MOUSE_SENSITIVITY;
        
        camera.mouseUpdate(xpos_delta, ypos_delta);
    }
    
    last_xpos = xpos;
    last_ypos = ypos;
}

void handleCursorEnter(GLFWwindow *window, int entered) {
    windowIsActive = entered;
}

GLVertexArray createGroundVertexArray() {
    int point_count = 0;
    GLfloat *vp, *vt, *vn;
    assert(load_obj_file("/Users/mattdonnelly/Documents/College/Computer Graphics/Assignment 4/obj/ground.obj", vp, vt, vn, point_count));
    
    GLBuffer points_vbo = GLBuffer::GLBuffer(vp, 3, sizeof(float) * 3 * point_count);
    GLBuffer tex_vbo = GLBuffer::GLBuffer(vt, 2, sizeof(float) * 2 * point_count);
    GLBuffer normals_vbo = GLBuffer(vn, 3, sizeof(float) * 3 * point_count);
    
    delete vp; delete vt; delete vn;
    
    std::vector<GLBuffer> buffers;
    buffers.emplace_back(points_vbo);
    buffers.emplace_back(tex_vbo);
    buffers.emplace_back(normals_vbo);
    
    return GLVertexArray(buffers, point_count);
}

GLVertexArray createCubeVertexArray() {
    int point_count = 0;
    GLfloat *vp, *vt, *vn;
    assert(load_obj_file("/Users/mattdonnelly/Documents/College/Computer Graphics/Assignment 4/obj/cube.obj", vp, vt, vn, point_count));
    
    GLBuffer points_vbo = GLBuffer::GLBuffer(vp, 3, sizeof(float) * 3 * point_count);
    GLBuffer tex_vbo = GLBuffer::GLBuffer(vt, 2, sizeof(float) * 2 * point_count);
    GLBuffer normals_vbo = GLBuffer(vn, 3, sizeof(float) * 3 * point_count);
    
    delete vp; delete vt; delete vn;
    
    std::vector<GLBuffer> buffers;
    buffers.emplace_back(points_vbo);
    buffers.emplace_back(tex_vbo);
    buffers.emplace_back(normals_vbo);
    
    return GLVertexArray(buffers, point_count);
}

GLProgram createShaderProgram() {
    std::vector<GLShader> shaders;
    shaders.emplace_back(GLShader::shaderFromFile("/Users/mattdonnelly/Documents/College/Computer Graphics/Assignment 4/Assignment 4/vertex_shader.glsl", GL_VERTEX_SHADER));
    shaders.emplace_back(GLShader::shaderFromFile("/Users/mattdonnelly/Documents/College/Computer Graphics/Assignment 4/Assignment 4/fragment_shader.glsl", GL_FRAGMENT_SHADER));
    
    GLProgram program = GLProgram(shaders);
    
    return program;
}

int main(int argc, const char * argv[]) {
    GLFWwindow *window = NULL;
    
    const GLubyte *renderer;
    const GLubyte *version;
    
    if (!glfwInit()) {
        fprintf(stderr, "ERROR: could not start GLFW3\n");
        return 1;
    }
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Assignment 4", NULL, NULL);
    if (!window) {
        fprintf (stderr, "ERROR: opening OS window\n");
        return 1;
    }
    
    glfwMakeContextCurrent(window);

    glfwSetCursorEnterCallback(window, handleCursorEnter);
    glfwSetCursorPosCallback(window, handleCursorPosition);
    
    glewExperimental = GL_TRUE;
    glewInit();
    
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    
    renderer = glGetString(GL_RENDERER);
    version = glGetString(GL_VERSION);
    std::cout << "Renderer: " << renderer << std::endl;
    std::cout << "OpenGL version supported " << version << std::endl;
    std::cout << std::endl;
    
    GLVertexArray ground_vao = createGroundVertexArray();
    GLVertexArray cube_vao = createCubeVertexArray();

    GLTexture ground_texture = GLTexture::GLTexture("/Users/mattdonnelly/Documents/College/Computer Graphics/Assignment 4/tex/ground.png", GL_RGBA);
    GLTexture cube_texture = GLTexture::GLTexture("/Users/mattdonnelly/Documents/College/Computer Graphics/Assignment 4/tex/cube.png", GL_RGBA);
    
    GLProgram shader_program = createShaderProgram();
    
    GLint texture_location = shader_program.uniform("tex");
    assert(texture_location > -1);
    
    const float fov = 45.0f;
    const float aspect = (double)GL_WIDTH / (double)GL_HEIGHT;
    const float near = 0.1f;
    const float far = 100.0f;
    
    camera = GLCamera(fov, aspect, near, far);
    camera.position = glm::vec3(0.0f, 3.0f, 10.0f);
    camera.speed = 10.0f;

    shader_program.use();
    
    const int proj_mat_location = shader_program.uniform("projection");
    const int view_mat_location = shader_program.uniform("view");
    const int model_mat_location = shader_program.uniform("model");

    while (!glfwWindowShouldClose(window)) {
        static double previous_seconds = glfwGetTime();
        double current_seconds = glfwGetTime();
        double elapsed_seconds = current_seconds - previous_seconds;
        previous_seconds = current_seconds;
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glViewport(0, 0, GL_WIDTH, GL_HEIGHT);
        
        glfwPollEvents();
        
        shader_program.use();

        glm::mat4 model, view, projection;
        camera.getMatricies(projection, view, model);
        
        shader_program.setUniform(proj_mat_location, projection);
        shader_program.setUniform(view_mat_location, view);
        shader_program.setUniform(model_mat_location, model);

        ///////// GROUND /////////
        
        ground_texture.bindTexture(GL_TEXTURE0);
        shader_program.setUniform(texture_location, 0);
        
        ground_vao.bind();
        ground_vao.draw();

        ///////// BOTTOM CUBE /////////
        
        cube_texture.bindTexture(GL_TEXTURE0);
        shader_program.setUniform(texture_location, 0);
        
        model = glm::translate(model, glm::vec3(0.0f, 1.1f, 0.0f));
        model = glm::rotate(model, (float)glfwGetTime() * 0.5f, glm::vec3(0.0f, 1.0f, 0.0f));
        shader_program.setUniform(model_mat_location, model);

        cube_vao.bind();
        cube_vao.draw();
        
        ///////// TOP CUBE /////////

        model = glm::translate(model, glm::vec3(0.0f, 2.01f, 0.0f));
        shader_program.setUniform(model_mat_location, model);
        
        cube_vao.bind();
        cube_vao.draw();

        if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_ESCAPE)) {
            glfwSetWindowShouldClose(window, 1);
        }
        
        if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_W)) {
            camera.moveForward(elapsed_seconds);
        }
        else if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_S)) {
            camera.moveBackward(elapsed_seconds);
        }
        
        if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_A)) {
            camera.moveLeft(elapsed_seconds);
        }
        else if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_D)) {
            camera.moveRight(elapsed_seconds);
        }
        
        if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_E)) {
            camera.moveUp(elapsed_seconds);
        }
        else if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_Q)) {
            camera.moveDown(elapsed_seconds);
        }

        glfwSwapBuffers(window);
    }
    
    glfwTerminate();
    return 0;
}
