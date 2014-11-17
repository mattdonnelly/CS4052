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
    this->speed = 5.0f;
    this->position = glm::vec3(0.0f, 0.0f, 0.0f);
    this->forward_direction = glm::vec3(0.0f, 0.0f, -1.0f);
    this->up_direction = glm::vec3(0.0f, 1.0f, 0.0f);
    this->orientation = glm::fquat(1.0f, 0.0f, 0.0f, 0.0f);
}

Camera::~Camera() {
    
}

void Camera::getMatricies(glm::mat4 &m, glm::mat4 &v, glm::mat4 &p) {
    view = glm::lookAt(position, position + forward_direction, up_direction);
    
    projection = glm::perspective(fov, aspect, near, far);
    model = glm::mat4(1.0f);
    heading = 0.0f;
    
    m = projection;
    v = view;
    p = model;
}

void Camera::mouseUpdate(float deltaX, float deltaY) {
    glm::vec3 axis = glm::cross(forward_direction, up_direction);
    glm::quat x_axis = glm::angleAxis(mouseY, axis);
    glm::quat y_axis = glm::angleAxis(mouseX, glm::vec3(0.0f, 1.0f, 0.0f));
    orientation =  x_axis * y_axis;
    
    rotation = glm::mat4_cast(orientation);
    forward_direction = glm::mat3(rotation) * forward_direction;
}

void Camera::moveForward(float delta) {
    position += speed * delta * forward_direction;
}

void Camera::moveBackward(float delta) {
    position -= speed * delta * forward_direction;
}

void Camera::moveLeft(float delta) {
    position += speed * delta * glm::cross(up_direction, forward_direction);
}

void Camera::moveRight(float delta) {
    position -= speed * delta * glm::cross(up_direction, forward_direction);
}

void Camera::moveUp(float delta) {
    position += speed * delta * up_direction;
}

void Camera::moveDown(float delta) {
    position -= speed * delta * up_direction;
}
