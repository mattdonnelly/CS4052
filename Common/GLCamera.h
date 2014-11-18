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
    GLCamera(double fov, double aspect, double near, double far);
    ~GLCamera();
    
    double aspect;
    double fov;
    double near;
    double far;
    
    float speed;
    
    glm::vec3 position;
    glm::vec3 forward_direction;
    glm::vec3 up_direction;

    glm::mat4 projection;
    glm::mat4 view;
    glm::mat4 model;
    
    void getMatricies(glm::mat4 &model, glm::mat4 &view, glm::mat4 &projection);
    
    void mouseUpdate(float deltaX, float deltaY);
    
    void moveForward(float delta);
    void moveBackward(float delta);
    void moveLeft(float delta);
    void moveRight(float delta);
    void moveUp(float delta);
    void moveDown(float delta);

private:
    
};
