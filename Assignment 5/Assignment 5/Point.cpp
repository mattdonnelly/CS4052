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

Point::Point(glm::vec3 location) : Drawable(location) {
    y = location.y;
    direction = rand() % 2 == 0 ? 1 : -1;
    
    vao = new GLVertexArray::GLVertexArray("/Users/mattdonnelly/Documents/College/Computer Graphics/Assignment 5/obj/point.obj");
    texture = new GLTexture::GLTexture("/Users/mattdonnelly/Documents/College/Computer Graphics/Assignment 5/tex/point.png");
}

std::vector<Point *> Point::generateRandomPoints(const int count, int min, int max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<int> dis(min, max);
    
    std::vector<Point *> points;
    for (int i = 0; i < count; i++) {
        double x = dis(gen);
        double y = 4.5;
        double z = dis(gen);
        Point *p = new Point(glm::vec3(x, y, z));
        points.push_back(p);
    }
    
    return points;
}

void Point::draw(GLProgram *shader_program) {
    if (!collected) {
        double oscillation = direction * sinf(glfwGetTime()) * 0.5f;
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

bool Point::locationWillCollide(glm::vec3 obj_loc) const {
    
    return glm::distance(location, obj_loc) < 3.0f;
}

bool Point::isCollidable() {
    return !collected;
}

int Point::tag() {
    return 0;
}
