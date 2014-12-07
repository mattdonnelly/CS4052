//
//  Drawable.cpp
//  Assignment 5
//
//  Created by Matt Donnelly on 06/12/2014.
//  Copyright (c) 2014 Matt Donnelly. All rights reserved.
//

#include "Drawable.h"

Drawable::Drawable(double x, double y, double z) : Drawable(glm::vec3(x, y, z)) { }

Drawable::Drawable(glm::vec3 loc) {
    location = loc;
    vao = NULL;
    texture = NULL;
    scale = glm::vec3(1.0f, 1.0f, 1.0f);
}

void Drawable::draw(GLProgram shader_program) {
    texture->bindTexture(GL_TEXTURE0);
    shader_program.setUniform("tex", 0);
    
    glm::mat4 model = glm::translate(glm::mat4(1.0f), location);
    model = glm::scale(model, scale);
    shader_program.setUniform("model", model);

    vao->draw();
}

GLVertexArray * Drawable::loadVertexArray(const char *file_name) {
    return new GLVertexArray(file_name);
}
