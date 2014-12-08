//
//  Gem.cpp
//  Assignment 5
//
//  Created by Matt Donnelly on 06/12/2014.
//  Copyright (c) 2014 Matt Donnelly. All rights reserved.
//

#include "Gem.h"
#include <GLFW/glfw3.h>
#include <iostream>

Gem::Gem(glm::vec3 location) : Drawable(location) {
    vao = new GLVertexArray::GLVertexArray("/Users/mattdonnelly/Documents/College/Computer Graphics/Assignment 5/obj/gem.obj");
    texture = new GLTexture::GLTexture("/Users/mattdonnelly/Documents/College/Computer Graphics/Assignment 5/tex/gem.png");
}

void Gem::draw(GLProgram *shader_program) {
    double oscillation = fabs(sinf(glfwGetTime()));
    scale = glm::vec3(oscillation, oscillation, oscillation);

    Drawable::draw(shader_program);
}

glm::vec3 Gem::collidableLocation() const {
    return location;
}

bool Gem::locationWillCollide(glm::vec3 obj_loc) const {
    return glm::distance(location, obj_loc) < 18.0f;
}

int Gem::tag() {
    return 1;
}
