//
//  Camera.cpp
//  Assignment 4
//
//  Created by Matt Donnelly on 16/11/2014.
//  Copyright (c) 2014 Matt Donnelly. All rights reserved.
//

#include "Camera.h"

#include <GLFW/glfw3.h>

Camera::Camera() : Camera(45.0f, 1.0f, 0.1f, 100.0f) {}

Camera::Camera(double fov, double aspect, double near, double far) {
    this->fov = fov;
    this->aspect = aspect;
    this->near = near;
    this->far = far;
    this->speed = 3.0f;
    this->position = glm::vec3(0.0f, 0.0f, 0.0f);
    this->forward_direction = glm::vec3(0.0f, 0.0f, -1.0f);
    this->up_direction = glm::vec3(0.0f, 1.0f, 0.0f);
    this->orientation = glm::fquat(1.0f, 0.0f, 0.0f, 0.0f);
}

Camera::~Camera() {
    
}

void Camera::update() {
    glm::vec3 axis = glm::cross(forward_direction, up_direction);
    glm::quat x_axis = glm::angleAxis(pitch, axis);
    glm::quat y_axis = glm::angleAxis(heading, glm::vec3(0.0f, 1.0f, 0.0f));
    glm::quat z_axis = glm::angleAxis(roll, glm::vec3(0.0f, 0.0f, 1.0f));
    orientation =  x_axis * y_axis * z_axis;
    
    rotation = glm::mat4_cast(orientation);
    forward_direction = glm::mat3(rotation) * forward_direction;
    view = glm::lookAt(position, position + forward_direction, up_direction);

    projection = glm::perspective(fov, aspect, near, far);
    model = glm::mat4(1.0f);
    heading = 0.0f;
}

void Camera::getMatricies(glm::mat4 &m, glm::mat4 &v, glm::mat4 &p) {
    m = projection;
    v = view;
    p = model;
}

void Camera::handleKey(int key, float delta) {
    if (key == GLFW_KEY_W) {        
        position += speed * delta * forward_direction;
        //position.z -= speed * delta;
    }
    else if (key == GLFW_KEY_S) {
        position -= speed * delta * forward_direction;
    }
    else if (key == GLFW_KEY_A) {
        heading += speed * delta;
    }
    else if (key == GLFW_KEY_D) {
        heading -= speed * delta;
    }
}
