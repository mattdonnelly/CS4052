//
//  Camera.h
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
#include <glm/gtx/transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera {
public:
    Camera();
    Camera(double fov, double aspect, double near, double far);
    ~Camera();
    
    double aspect;
    double fov;
    double near;
    double far;
    double speed;
    
    float roll;
    float heading;
    float pitch;
    
    glm::vec3 position;
    glm::quat orientation;

    glm::mat4 projection;
    glm::mat4 view;
    glm::mat4 model;
    
    void move(GLfloat vel);
    void update();
    void getMatricies(glm::mat4 &model, glm::mat4 &view, glm::mat4 &projection);
    
    void handleKey(int key, double delta);
};
