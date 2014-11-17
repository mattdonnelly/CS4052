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
#include <glm/gtc/type_ptr.hpp>
#include <math.h>

#include "Camera.h"
#include "GLBuffer.h"
#include "GLVertexArray.h"
#include "GLShader.h"
#include "GLTexture.h"
#include "GLProgram.h"
#include "stb_image.h"
#include "obj_parser.h"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

#define RETINA 1

#if RETINA
    #define GL_WIDTH (WINDOW_WIDTH  * 2)
    #define GL_HEIGHT (WINDOW_HEIGHT  * 2)
#else
    #define GLWIDTH WINDOW_WIDTH
    #define GL_HEIGHT WINDOW_HEIGHT
#endif

GLProgram createShaderProgram() {
    std::vector<GLShader> shaders;
    shaders.emplace_back(GLShader::shaderFromFile("/Users/mattdonnelly/Documents/College/Computer Graphics/Assignment 4/Assignment 4/vertex_shader.glsl", GL_VERTEX_SHADER));
    shaders.emplace_back(GLShader::shaderFromFile("/Users/mattdonnelly/Documents/College/Computer Graphics/Assignment 4/Assignment 4/fragment_shader.glsl", GL_FRAGMENT_SHADER));
    
    GLProgram program = GLProgram(shaders);
    
    return program;
}

/*void keyCallback(GLFWwindow *window,int key, int scan_code, int action, int mods) {
    switch (key) {
        case GLFW_KEY_W:
            camera.move(FORWARD);
            break;
        case GLFW_KEY_A:
            camera.move(LEFT);
            break;
        case GLFW_KEY_S:
            camera.move(BACK);
            break;
        case GLFW_KEY_D:
            camera.move(RIGHT);
            break;
        case GLFW_KEY_Q:
            camera.move(DOWN);
            break;
        case GLFW_KEY_E:
            camera.move(UP);
            break;
    }
}*/

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
    //glfwSetKeyCallback(window, keyCallback);
    
    glewExperimental = GL_TRUE;
    glewInit();
    
    renderer = glGetString(GL_RENDERER);
    version = glGetString(GL_VERSION);
    std::cout << "Renderer: " << renderer << std::endl;
    std::cout << "OpenGL version supported " << version << std::endl;
    std::cout << std::endl;

    GLfloat points[] = {
         0.0f,	0.5f,	0.0f,
         0.5f, -0.5f,	0.0f,
        -0.5f, -0.5f,	0.0f
    };
    
    float normals[] = {
        0.0f, 0.0f,  1.0f,
        0.0f, 0.0f,  1.0f,
        0.0f, 0.0f,  1.0f,
    };
    
    GLBuffer points_vbo = GLBuffer(points, 3, 9 * sizeof(float));
    GLBuffer normals_vbo = GLBuffer(normals, 3, 9 * sizeof(float));
    
    std::vector<GLBuffer> buffers;
    buffers.emplace_back(points_vbo);
    buffers.emplace_back(normals_vbo);
    
    GLVertexArray vao = GLVertexArray(buffers);
    
    GLProgram shader_program = createShaderProgram();
    
    const float fov = 45.0f;
    const float aspect = (double)GL_WIDTH / (double)GL_HEIGHT;
    const float near = 0.1f;
    const float far = 100.0f;
    
    Camera camera = Camera(fov, aspect, near, far);
    camera.setPosition(0.0f, 0.0f, 2.0f);
    camera.setLookAt(0.0f, 0.0f, 0.0f);
    camera.setPitch(0.1f);
    camera.setHeading(0.1f);
                           
    shader_program.use();

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CW);
    
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glViewport(0, 0, GL_WIDTH, GL_HEIGHT);
        
        shader_program.use();

        glm::mat4 model, view, projection;
        
        camera.update();
        camera.getMatricies(projection, view, model);
        
        shader_program.setUniform("projection", projection);
        shader_program.setUniform("view", view);
        shader_program.setUniform("model", model);
        
        vao.bind();
        
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwPollEvents();

        if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_ESCAPE)) {
            glfwSetWindowShouldClose(window, 1);
        }

        glfwSwapBuffers(window);
    }
    
    glfwTerminate();
    return 0;
}
