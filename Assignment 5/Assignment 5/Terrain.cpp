//
//  Terrain.cpp
//  Assignment 5
//
//  Created by Matt Donnelly on 06/12/2014.
//  Copyright (c) 2014 Matt Donnelly. All rights reserved.
//

#include "Terrain.h"

Terrain::Terrain() : Drawable(0.0f, 0.0f, 0.0f), light(glm::vec3(0.0f, 15.0f, 0.0f),
                                                       glm::vec4(0.1f, 0.2f,  0.2f, 200.0f),
                                                       glm::vec4(0.6f, 0.7f,  0.6f, 200.0f),
                                                       glm::vec4(1.0f, 1.0f,  1.0f, 200.0f))
{
    vao = new GLVertexArray::GLVertexArray("/Users/mattdonnelly/Documents/College/Computer Graphics/Assignment 5/obj/terrain.obj");
    texture = new GLTexture::GLTexture("/Users/mattdonnelly/Documents/College/Computer Graphics/Assignment 5/tex/grass.png");
}

bool Terrain::locationWillCollide(glm::vec3 location) const {
    return location.x < -77.f || location.x > 77.0f ||
           location.z < -77.f || location.z > 77.0f;
}

void Terrain::draw(GLProgram *shader_program) {
    light.render_light_source(shader_program);
    Drawable::draw(shader_program);
}

