//
//  GLCamera.h
//  Assignment 4
//
//  Created by Matt Donnelly on 16/11/2014.
//  Copyright (c) 2014 Matt Donnelly. All rights reserved.
//

#pragma once

#define GLM_FORCE_RADIANS

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

class GLCamera {
public:
    GLCamera();
    
    float speed;
    
    glm::vec3 position;
    glm::vec3 forward_direction;
    glm::vec3 up_direction;
    
    virtual glm::mat4 getViewMatrix();

    virtual void mouseUpdate(float deltaX, float deltaY);
    
    virtual void moveForward(float delta);
    virtual void moveBackward(float delta);
    virtual void moveLeft(float delta);
    virtual void moveRight(float delta);
    virtual void moveUp(float delta);
    virtual void moveDown(float delta);
};
