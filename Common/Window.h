//
//  Window.h
//  Assignment 5
//
//  Created by Matt Donnelly on 06/12/2014.
//  Copyright (c) 2014 Matt Donnelly. All rights reserved.
//

#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "GLProgram.h"
#include "Player.h"

class Window {
public:
    Window(const char *t, int w, int h);
    
    const char *title;
    const int width;
    const int height;
    
    bool isActive;
    
    float aspectRatio() const;
    
    GLCamera *camera;
    
    void didResize();
    void setShaderProgram(GLProgram *program);
    
    bool shouldClose();

    double getTime();

    void clear();
    void swapBuffers();
    void pollEvents();

private:
    GLFWwindow *_window;
    double _delta;
    GLProgram *_program;
};
