//
//  GLCamera.cpp
//  Assignment 4
//
//  Created by Matt Donnelly on 16/11/2014.
//  Copyright (c) 2014 Matt Donnelly. All rights reserved.
//

#include "GLCamera.h"

#include <GLFW/glfw3.h>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/quaternion.hpp>

GLCamera::GLCamera() : GLCamera(45.0f, 1.0f, 0.1f, 100.0f) {}

GLCamera::GLCamera(double fov, double aspect, double near, double far) {
    this->fov = fov;
    this->aspect = aspect;
    this->near = near;
    this->far = far;
    this->speed = 5.0f;
    this->position = glm::vec3(0.0f, 0.0f, 0.0f);
    this->forward_direction = glm::vec3(0.0f, 0.0f, -1.0f);
    this->up_direction = glm::vec3(0.0f, 1.0f, 0.0f);
}

GLCamera::~GLCamera() {
    
}

void GLCamera::getMatricies(glm::mat4 &m, glm::mat4 &v, glm::mat4 &p) {
    projection = glm::perspective(fov, aspect, near, far);
    view = glm::lookAt(position, position + forward_direction, up_direction);
    model = glm::mat4(1.0f);
    
    m = projection;
    v = view;
    p = model;
}

void GLCamera::mouseUpdate(float deltaX, float deltaY) {
    glm::vec3 x_axis = glm::cross(forward_direction, up_direction);
    glm::quat pitch = glm::angleAxis(deltaY, x_axis);
    glm::quat yaw = glm::angleAxis(deltaX, up_direction);
    glm::quat orientation =  yaw * pitch;
    
    glm::mat4 rotation = glm::mat4_cast(orientation);
    forward_direction = glm::mat3(rotation) * forward_direction;
}

void GLCamera::moveForward(float delta) {
    position += speed * delta * forward_direction;
}

void GLCamera::moveBackward(float delta) {
    position -= speed * delta * forward_direction;
}

void GLCamera::moveLeft(float delta) {
    position += speed * delta * glm::cross(up_direction, forward_direction);
}

void GLCamera::moveRight(float delta) {
    position -= speed * delta * glm::cross(up_direction, forward_direction);
}

void GLCamera::moveUp(float delta) {
    position += speed * delta * up_direction;
}

void GLCamera::moveDown(float delta) {
    position -= speed * delta * up_direction;
}