//
//  main.cpp
//  Assignment0
//
//  Created by Matt Donnelly on 23/09/2014.
//  Copyright (c) 2014 Matt Donnelly. All rights reserved.
//

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <iostream>

void checkShaderStatus(GLuint shader) {
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    
    if (status == GL_FALSE) {
        GLint infoLogLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
        
        GLchar *strInfoLog = new GLchar[infoLogLength + 1];
        glGetShaderInfoLog(shader, infoLogLength, NULL, strInfoLog);
        
        fprintf(stderr, "Compilation error in shader: %s\n", strInfoLog);
        delete[] strInfoLog;
        
        glDeleteShader(shader);
    }
}

int main(int argc, const char *argv[]) {
    if (!glfwInit()) {
        fprintf (stderr, "ERROR: could not start GLFW3\n");
        return 1;
    }
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    GLFWwindow *window = glfwCreateWindow(640, 640, "Assignment 0", NULL, NULL);
    if (!window) {
        fprintf (stderr, "ERROR: could not open window with GLFW3\n");
        glfwTerminate();
        return 1;
    }
    
    glfwMakeContextCurrent(window);
    
    glewExperimental = GL_TRUE;
    glewInit();
    
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    
    float vertices[] = {
        -0.5f,  0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        
        -0.5f,  0.5f, 0.0f,
        0.5f,  0.5f, 0.0f,
        0.5f, -0.5f, 0.0f
    };
    
    float colours[] = {
        1.0f, 0.0f,  0.0f,
        1.0f, 1.0f,  0.0f,
        1.0f, 0.0f,  0.0f,
        
        1.0f, 0.0f,  0.0f,
        1.0f, 1.0f,  0.0f,
        1.0f, 0.0f,  0.0f
    };
    
    GLuint verticesBuffer = NULL;
    glGenBuffers(1, &verticesBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, verticesBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    GLuint coloursBuffer = NULL;
    glGenBuffers(1, &coloursBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, coloursBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colours), colours, GL_STATIC_DRAW);
    
    GLuint vao = NULL;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    glBindBuffer(GL_ARRAY_BUFFER, verticesBuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glBindBuffer(GL_ARRAY_BUFFER, coloursBuffer);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    
    const char *vertex_shader =
    "#version 400\n"
    "layout(location = 0) in vec3 vertex_position;"
    "layout(location = 1) in vec3 vertex_colour;"
    "out vec3 colour;"
    "void main() {"
    "    colour = vertex_colour;"
    "    gl_Position = vec4(vertex_position * 0.5, 1.0);"
    "}";
    
    const char *fragment_shader =
    "#version 400\n"
    "in vec3 colour;"
    "out vec4 frag_colour;"
    "void main() {"
    "    frag_colour = vec4(colour, 1.0);"
    "}";
    
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertex_shader, NULL);
    glCompileShader(vs);
    checkShaderStatus(vs);
    
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragment_shader, NULL);
    glCompileShader(fs);
    checkShaderStatus(fs);
    
    GLuint shader_programme = glCreateProgram ();
    glAttachShader(shader_programme, fs);
    glAttachShader(shader_programme, vs);
    
    glBindAttribLocation(shader_programme, 0, "vertex_position");
    glBindAttribLocation(shader_programme, 1, "vertex_colour");
    
    glLinkProgram (shader_programme);
    
    while (!glfwWindowShouldClose (window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        glUseProgram(shader_programme);
        glBindVertexArray(vao);
        
        glDrawArrays(GL_TRIANGLES, 0, 6);
        
        glfwPollEvents();
        
        glfwSwapBuffers(window);
    }
    
    glfwTerminate();
    
    return 0;
}
