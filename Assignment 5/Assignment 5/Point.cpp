//
//  Point.cpp
//  Assignment 5
//
//  Created by Matt Donnelly on 06/12/2014.
//  Copyright (c) 2014 Matt Donnelly. All rights reserved.
//

#include "Point.h"
#include "AudioManager.h"

#include <GLFW/glfw3.h>
#include <random>
#include <iostream>

Point::Point(glm::vec3 location) : Drawable(location) {
    y = location.y + ((double)rand() / (RAND_MAX));
    
    vao = new GLVertexArray::GLVertexArray("/Users/mattdonnelly/Documents/College/Computer Graphics/Assignment 5/obj/point.obj");
    texture = new GLTexture::GLTexture("/Users/mattdonnelly/Documents/College/Computer Graphics/Assignment 5/tex/point.png", GL_RGB);
}

std::vector<Point *> Point::generateRandomPoints(const int count) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<int> dis(-70, 70);
    
    std::vector<Point *> points;
    for (int i = 0; i < count; i++) {
        double x = dis(gen);
        double y = ((double)rand() / (RAND_MAX)) + 4.0;
        double z = dis(gen);
        Point *p = new Point(glm::vec3(x, y, z));
        points.push_back(p);
    }
    
    return points;
}

void Point::draw(GLProgram shader_program) {
    if (!collected) {
        double oscillation = sinf(glfwGetTime());
        pitch = glfwGetTime();
        location = glm::vec3(location.x, y + oscillation, location.z);

        Drawable::draw(shader_program);
    }
}

void Point::collide(Collidable *obj) {
    if (!collected) {
        AudioManager::sharedManager()->playItemPickUp();
    }
    
    collected = true;
}

glm::vec3 Point::collidableLocation() const {
    return location;
}
