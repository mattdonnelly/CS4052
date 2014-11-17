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
    this->fov = fov;
    this->aspect = aspect;
    this->near = near;
    this->far = far;
    up_direction = glm::vec3(0.0f, 1.0f, 0.0f);
    position = glm::vec3(0.0f, 0.0f, 1.0f);
    look_at = glm::vec3(0.0f, 0.0f, 0.0f);
    orientation = glm::fquat(1.0f, 0.0f, 0.0f, 0.0f);
}

Camera::~Camera() {
    
}

void Camera::setPosition(double x, double y, double z) {
    position.x = x;
    position.y = y;
    position.z = z;
    needsUpdate = true;
}

void Camera::setLookAt(double x, double y, double z) {
    look_at.x = x;
    look_at.y = y;
    look_at.z = z;
    needsUpdate = true;
}

void Camera::setPitch(float pitch) {
    this->pitch = pitch;
    needsUpdate = true;
}

void Camera::setHeading(float heading) {
    this->heading = heading;
    needsUpdate = true;
}

void Camera::update() {
    if (needsUpdate) {
        orientation = glm::fquat(1.0f, 0.0f, 0.0f, 0.0f);
        
        glm::fquat pitch_angle = glm::angleAxis(-pitch, glm::vec3(1, 0, 0));
        orientation = pitch_angle * orientation;
        orientation = glm::normalize(orientation);

        glm::fquat heading_angle = glm::angleAxis(heading, up_direction);
        orientation = orientation * heading_angle;
        orientation = glm::normalize(orientation);
        
        view = glm::mat4_cast(orientation);
        glm::vec3 m_xaxis = glm::vec3(view[0][0], view[1][0], view[2][0]);
        glm::vec3 m_yaxis = glm::vec3(view[0][1], view[1][1], view[2][1]);
        glm::vec3 m_zaxis = glm::vec3(view[0][2], view[1][2], view[2][2]);

        view[3][0] = -glm::dot(m_xaxis, position);
        view[3][1] = -glm::dot(m_yaxis, position);
        view[3][2] = -glm::dot(m_zaxis, position);

        projection = glm::perspective(fov, aspect, near, far);
        model = glm::mat4(1.0f);
    }
}

void Camera::getMatricies(glm::mat4 &m, glm::mat4 &v, glm::mat4 &p) {
    m = projection;
    v = view;
    p = model;
}
