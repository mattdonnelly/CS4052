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

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera {
public:
    Camera(double fov, double aspect, double near, double far);
    ~Camera();
    
    double aspect();
    double fov();
    double near();
    double far();
    
    glm::vec3 up_direction();
    glm::vec3 position();
    glm::vec3 look_at();
    
    void setPosition(double x, double y, double z);
    void setLookAt(double x, double y, double z);
    
    void setRoll(float roll);
    void setPitch(float pitch);
    void setHeading(float heading);
    
    float roll();
    float pitch();
    float heading();
    
    void lookAt(float x, float y, float z);

    void update();
    void getMatricies(glm::mat4 &model, glm::mat4 &view, glm::mat4 &projection);

private:
    double _aspect;
    double _fov;
    double _near;
    double _far;
    
    float _roll;
    float _heading;
    float _pitch;
    
    glm::vec3 _up_direction;
    glm::vec3 _position;
    glm::vec3 _look_at;
    
    glm::mat4 projection;
    glm::mat4 view;
    glm::mat4 model;
    
    bool needsUpdate;
};
