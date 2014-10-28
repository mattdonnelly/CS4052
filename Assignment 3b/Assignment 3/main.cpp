//
//  main.cpp
//  Assignment 3
//
//  Created by Matt Donnelly on 27/10/2014.
//  Copyright (c) 2014 Matt Donnelly. All rights reserved.
//

#define STB_IMAGE_IMPLEMENTATION
#define GLM_FORCE_RADIANS

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <assert.h>
#include <string.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "stb_image.h"
#include "obj_parser.h"

#define DEGREES_TO_RADIANS(angle) ((angle) / 180.0 * M_PI)

const int gl_width = 800;
const int gl_height = 800;

GLuint loadTexture() {
    GLuint texture;
    
    std::string filePath = "/Users/mattdonnelly/Documents/College/Computer Graphics/Assignment 3b/Assignment 3/texture.png";
    
    int width, height, channels;
    unsigned char* pixels = stbi_load(filePath.c_str(), &width, &height, &channels, 0);
    
    std::cout << "Loaded texture: " << width << "x" << height << " " << channels << " channels" << std::endl;
    
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (GLsizei)width, (GLsizei)height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    glBindTexture(GL_TEXTURE_2D, 0);
    
    free(pixels);
    
    return texture;
}

std::string readShaderFile(std::string filename) {
    std::ifstream ifile(filename);
    std::string text;
    
    if (!ifile.is_open()) {
        std::cout << "Error: Could not open file" << std::endl;
        return "";
    }
    
    while(ifile.good()) {
        std::string line;
        std::getline(ifile, line);
        text.append(line + "\n");
    }
    
    text += '\0';
    
    return text;
}

void printShaderStatus(GLuint shader) {
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    
    if (status == GL_FALSE) {
        GLint infoLogLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
        
        GLchar *strInfoLog = (char *)malloc(infoLogLength + 1);
        glGetShaderInfoLog(shader, infoLogLength, NULL, strInfoLog);
        
        fprintf(stderr, "Compilation error in shader: %s\n", strInfoLog);
        free(strInfoLog);
        
        glDeleteShader(shader);
    }
}

GLuint createShaderProgramme() {
    GLuint shader_programme;
    
    std::string vertex_shader_str = readShaderFile("/Users/mattdonnelly/Documents/College/Computer Graphics/Assignment 3b/Assignment 3/vertex_shader.vert");
    GLchar const *vertex_shader_source = vertex_shader_str.c_str();
    
    std::string fragment_shader_str = readShaderFile("/Users/mattdonnelly/Documents/College/Computer Graphics/Assignment 3b/Assignment 3/fragment_shader.frag");
    GLchar const *fragment_shader_source = fragment_shader_str.c_str();
    
    GLuint vs, fs;
    vs = glCreateShader(GL_VERTEX_SHADER);
    fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(vs, 1, &vertex_shader_source, NULL);
    glShaderSource(fs, 1, &fragment_shader_source, NULL);
    
    glCompileShader(vs);
    printShaderStatus(vs);
    
    glCompileShader(fs);
    printShaderStatus(fs);
    
    shader_programme = glCreateProgram ();
    glAttachShader(shader_programme, fs);
    glAttachShader(shader_programme, vs);
    glLinkProgram (shader_programme);
    
    return shader_programme;
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
    
    window = glfwCreateWindow(gl_width, gl_height, "Assignment 2", NULL, NULL);
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

    {
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        
        GLfloat *vp;
        GLfloat *vn;
        GLfloat *vt;
        assert(load_obj_file("/Users/mattdonnelly/Documents/College/Computer Graphics/Assignment 3b/Assignment 3/cube.obj", vp, vt, vn, point_count));
        
        GLuint points_vbo;
        glGenBuffers(1, &points_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * point_count, vp, GL_STATIC_DRAW);
        
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        
        delete vp;
        delete vn;
        delete vt;
    }
    
    GLuint shader_programme = createShaderProgramme();
    
    int M_loc = glGetUniformLocation (shader_programme, "M");
    assert(M_loc > -1);
    
    int V_loc = glGetUniformLocation (shader_programme, "V");
    assert(M_loc > -1);
    
    int P_loc = glGetUniformLocation (shader_programme, "P");
    assert(M_loc > -1);
    
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glClearColor(0.5, 0.5, 0.5, 1.0);
    
    GLfloat rotating_speed = 2.0f;
    GLfloat last_angle = 0.0f;
    
    while (!glfwWindowShouldClose(window)) {
        static GLdouble previous_seconds = glfwGetTime();
        double current_seconds = glfwGetTime();
        double elapsed_seconds = current_seconds - previous_seconds;
        previous_seconds = current_seconds;
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        glUseProgram(shader_programme);
        
        glBindVertexArray(vao);
        
        if (last_angle > 359.0f) {
            last_angle = 0.0f;
        }
        
        last_angle += elapsed_seconds * rotating_speed;
        
        glm::mat4 projection = glm::perspective(45.0f, 1.0f, 1.0f, 10.0f);
        glm::mat4 view = glm::lookAt(glm::vec3(2.5f, 2.5f, 2.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 model = glm::rotate(glm::mat4(1.0f), last_angle, glm::vec3(0, 1, 0));
        model = glm::scale(model, glm::vec3(0.75f));
        glUniformMatrix4fv(P_loc, 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(V_loc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(M_loc, 1, GL_FALSE, glm::value_ptr(model));
        
        glDrawArrays(GL_TRIANGLES, 0, point_count);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }
    
    return 0;
    
}
