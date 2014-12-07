//
//  Window.cpp
//  Assignment 5
//
//  Created by Matt Donnelly on 06/12/2014.
//  Copyright (c) 2014 Matt Donnelly. All rights reserved.
//

#include "Window.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

#define RETINA

#ifdef RETINA
    #define MOUSE_SENSITIVITY 0.0056f
#else
    #define MOUSE_SENSITIVITY 0.02f
#endif

bool positionInWindow(GLFWwindow *window, double mouseX, double mouseY) {
    Window *win = static_cast<Window *>(glfwGetWindowUserPointer(window));
    
    int windowX, windowY;
    glfwGetWindowPos(window, &windowX, &windowY);
    
    return (mouseX > 0 && mouseX < win->width) && (mouseY > 0 && mouseY < win->height);
}

void handleCursorPosition(GLFWwindow *window, double xpos, double ypos) {
    Window *win = static_cast<Window*>(glfwGetWindowUserPointer(window));
    
    static double last_xpos = xpos;
    static double last_ypos = ypos;
    
    if (win->isActive && positionInWindow(window, xpos, ypos)) {
        double xpos_delta = (last_xpos - xpos) * MOUSE_SENSITIVITY;
        double ypos_delta = (last_ypos - ypos) * MOUSE_SENSITIVITY;
        
        win->camera->mouseUpdate(xpos_delta, ypos_delta);
    }
    
    last_xpos = xpos;
    last_ypos = ypos;
}

void handleCursorEnter(GLFWwindow *window, int entered) {
    Window *win = static_cast<Window*>(glfwGetWindowUserPointer(window));
    win->isActive = entered;
}

void handleWindowSize(GLFWwindow *window, int width, int height) {
    Window *win = static_cast<Window*>(glfwGetWindowUserPointer(window));
    win->didResize();
}

Window::Window(const char *t, int w, int h) : title(t), width(w), height(h) {
    _window = NULL;
    isActive = true;
    
    const GLubyte *renderer;
    const GLubyte *version;
    
    if (!glfwInit()) {
        throw std::runtime_error("ERROR: could not start GLFW3\n");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    _window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!_window) {
        throw std::runtime_error("ERROR: opening OS window\n");
    }
    
    glfwMakeContextCurrent(_window);
    
    glfwSetWindowUserPointer(_window, this);
    glfwSetCursorEnterCallback(_window, handleCursorEnter);
    glfwSetCursorPosCallback(_window, handleCursorPosition);
    glfwSetWindowSizeCallback(_window, handleWindowSize);
    
    glewExperimental = GL_TRUE;
    glewInit();

    glClearColor(0.05f, 0.1f, 0.1f, 1.0f);
    glClearDepth(1);
    glEnable(GL_DEPTH_TEST);
    
    renderer = glGetString(GL_RENDERER);
    version = glGetString(GL_VERSION);
    std::cout << "Renderer: " << renderer << std::endl;
    std::cout << "OpenGL version supported " << version << std::endl;
    std::cout << std::endl;
}

void Window::setShaderProgram(GLProgram *p) {
    _program = p;
    didResize();
}

void Window::didResize() {
    int width, height;
    glfwGetWindowSize(_window, &width, &height);
    glm::mat4 projection = glm::perspective((float)45.0f, aspectRatio(), 0.1f, 1000.0f);
    _program->setUniform("projection", projection);
}

float Window::aspectRatio() const {
    return (float)width / (float)height;
}

bool Window::shouldClose() {
    return glfwWindowShouldClose(_window);
}

double Window::getTime() {
    return glfwGetTime();
}

void Window::clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::swapBuffers() {
    static double previous_seconds = getTime();
    double current_seconds = getTime();
    double elapsed_seconds = current_seconds - previous_seconds;
    previous_seconds = current_seconds;
    
    _delta = elapsed_seconds;
    
    glfwSwapBuffers(_window);
}

void Window::pollEvents() {
    glfwPollEvents();
    
    if (GLFW_PRESS == glfwGetKey(_window, GLFW_KEY_ESCAPE)) {
        glfwSetWindowShouldClose(_window, 1);
    }
    
    if (GLFW_PRESS == glfwGetKey(_window, GLFW_KEY_W)) {
        camera->moveForward(_delta);
    }
    else if (GLFW_PRESS == glfwGetKey(_window, GLFW_KEY_S)) {
        camera->moveBackward(_delta);
    }
    
    if (GLFW_PRESS == glfwGetKey(_window, GLFW_KEY_A)) {
        camera->moveLeft(_delta);
    }
    else if (GLFW_PRESS == glfwGetKey(_window, GLFW_KEY_D)) {
        camera->moveRight(_delta);
    }
}
