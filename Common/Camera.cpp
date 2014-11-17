//
//  Camera.cpp
//  Assignment 4
//
//  Created by Matt Donnelly on 16/11/2014.
//  Copyright (c) 2014 Matt Donnelly. All rights reserved.
//

#include "Camera.h"

#include <GLFW/glfw3.h>

Camera::Camera(double fov, double aspect, double near, double far) {
    _fov = fov;
    _aspect = aspect;
    _near = near;
    _far = far;
    _up_direction = glm::vec3(0.0f, 1.0f, 0.0f);
    _position = glm::vec3(0.0f, 0.0f, 1.0f);
    _look_at = glm::vec3(0.0f, 0.0f, 0.0f);
}

Camera::~Camera() {
    
}

double Camera::aspect() {
    return _aspect;
}

double Camera::fov() {
    return _fov;
}

double Camera::near() {
    return _near;
}

double Camera::far() {
    return _far;
}


void Camera::setPosition(double x, double y, double z) {
    _position.x = x;
    _position.y = y;
    _position.z = z;
    needsUpdate = true;
}

void Camera::setLookAt(double x, double y, double z) {
    _look_at.x = x;
    _look_at.y = y;
    _look_at.z = z;
    needsUpdate = true;
}

void Camera::setRoll(float roll) {
    _roll = roll;
    needsUpdate = true;
}

void Camera::setPitch(float pitch) {
    _pitch = pitch;
    needsUpdate = true;
}

void Camera::setHeading(float heading) {
    _heading = heading;
    needsUpdate = true;
}

float Camera::roll() {
    return _roll;
}

float Camera::pitch() {
    return _pitch;
}

float Camera::heading() {
    return _heading;
}

void Camera::update() {
    if (needsUpdate) {
        glm::vec3 camera_direction = glm::normalize(_look_at - _position);
        
        glm::vec3 axis = glm::cross(camera_direction, _up_direction);
        glm::quat pitch_quat = glm::angleAxis(_pitch, axis);
        
        glm::quat heading_quat = glm::angleAxis(_heading, _up_direction);
        
        glm::quat temp = glm::cross(pitch_quat, heading_quat);
        temp = glm::normalize(temp);
        
        camera_direction = glm::rotate(temp, camera_direction);
        
        _look_at = _position + camera_direction;

        projection = glm::perspective(_fov, _aspect, _near, _far);
        view = glm::lookAt(_position, _look_at, _up_direction);
        model = glm::mat4(1.0f);
        
        needsUpdate = false;
    }
}

void Camera::getMatricies(glm::mat4 &m, glm::mat4 &v, glm::mat4 &p) {
    m = projection;
    v = view;
    p = model;
}
