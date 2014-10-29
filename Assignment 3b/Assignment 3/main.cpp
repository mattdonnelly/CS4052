//
//  main.cpp
//  Assignment 3
//
//  Created by Matt Donnelly on 27/10/2014.
//  Copyright (c) 2014 Matt Donnelly. All rights reserved.
//

#define STB_IMAGE_IMPLEMENTATION
#define GLM_FORCE_RADIANS

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include "GLBuffer.h"
#include "GLShader.h"
#include "GLTexture.h"
#include "GLProgram.h"
#include "stb_image.h"
#include "obj_parser.h"

const int gl_width = 800;
const int gl_height = 800;

GLProgram createShaderProgram() {
    std::vector<GLShader> shaders;
    shaders.push_back(GLShader::shaderFromFile("/Users/mattdonnelly/Documents/College/Computer Graphics/Assignment 3b/Assignment 3/vertex_shader.vert", GL_VERTEX_SHADER));
    shaders.push_back(GLShader::shaderFromFile("/Users/mattdonnelly/Documents/College/Computer Graphics/Assignment 3b/Assignment 3/fragment_shader.frag", GL_FRAGMENT_SHADER));
    
    GLProgram program = GLProgram(shaders);
    
    return program;
}

int main() {
    GLFWwindow *window = NULL;
    
    GLuint vao;
    int point_count = 0;
    
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
    
    window = glfwCreateWindow(gl_width, gl_height, "Assignment 3", NULL, NULL);
    if (!window) {
        fprintf (stderr, "ERROR: opening OS window\n");
        return 1;
    }
    
    glfwMakeContextCurrent(window);
    
    glewExperimental = GL_TRUE;
    glewInit();
    
    renderer = glGetString(GL_RENDERER);
    version = glGetString(GL_VERSION);
    std::cout << "Renderer: " << renderer << std::endl;
    std::cout << "OpenGL version supported " << version << std::endl;
    std::cout << std::endl;
    
    GLBuffer buffer = GLBuffer::GLBuffer();

    {
        GLfloat *vp;
        GLfloat *vt;
        GLfloat *vn;
        assert(load_obj_file("/Users/mattdonnelly/Documents/College/Computer Graphics/Assignment 3b/Assignment 3/cube.obj", vp, vt, vn, point_count));

        buffer.bufferObject(vp, 3, sizeof(float) * 3 * point_count);
        buffer.bufferObject(vt, 2, sizeof(float) * 3 * point_count);
        
        delete vp;
        delete vn;
        delete vt;
    }
    
    GLTexture texture = GLTexture::GLTexture("/Users/mattdonnelly/Documents/College/Computer Graphics/Assignment 3b/Assignment 3/texture.png", GL_RGBA);
    
    GLProgram program = createShaderProgram();

    GLint texture_id = program.uniform("tex");
    assert(texture_id > -1);
    
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glClearColor(0.5, 0.5, 0.5, 1.0);
    
    GLfloat rotating_speed = 1.5f;
    GLfloat last_angle = 0.0f;
    
    while (!glfwWindowShouldClose(window)) {
        static GLdouble previous_seconds = glfwGetTime();
        double current_seconds = glfwGetTime();
        double elapsed_seconds = current_seconds - previous_seconds;
        previous_seconds = current_seconds;
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        program.use();
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture.object());
        program.setUniform("tex", 0);
        
        glBindVertexArray(vao);
        
        if (last_angle > M_PI * 2) {
            last_angle = 0.0f;
        }
        
        last_angle += elapsed_seconds * rotating_speed;
        
        glm::mat4 projection = glm::perspective(45.0f, 1.0f, 1.0f, 10.0f);
        glm::mat4 view = glm::lookAt(glm::vec3(2.5f, 2.5f, 2.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 2.0f, 0.0f));
        glm::mat4 model = glm::rotate(glm::mat4(1.0f), last_angle, glm::vec3(0, 1, 0));
        model = glm::scale(model, glm::vec3(0.75f));
        
        program.setUniform("P", projection);
        program.setUniform("V", view);
        program.setUniform("M", model);
        
        glDrawArrays(GL_TRIANGLES, 0, point_count);
        
        glDeleteTextures((GLsizei)1, (const GLuint*)(&texture_id));

        glfwPollEvents();
        glfwSwapBuffers(window);
    }
    
    return 0;
    
}
