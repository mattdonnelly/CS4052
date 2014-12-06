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

#include "GLCamera.h"
#include "Player.h"

class Window {
public:
    Window(const char *t, int w, int h);
    
    const char *title;
    const int width;
    const int height;
    
    bool isActive;
    
    float aspectRatio() const;
    
    Player *player;
    
    bool shouldClose();
    double getTime();
    void presentBuffer();
    void pollEvents();
    
private:
    GLFWwindow *_window;
    double _delta;
};
