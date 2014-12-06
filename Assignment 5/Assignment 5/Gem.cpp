//
//  Gem.cpp
//  Assignment 5
//
//  Created by Matt Donnelly on 06/12/2014.
//  Copyright (c) 2014 Matt Donnelly. All rights reserved.
//

#include "Gem.h"

Gem::Gem(glm::vec3 location) : Drawable(location) {
    vao = Drawable::loadVertexArray("/Users/mattdonnelly/Documents/College/Computer Graphics/Assignment 5/obj/gem.obj");
    texture = new GLTexture::GLTexture("/Users/mattdonnelly/Documents/College/Computer Graphics/Assignment 5/tex/gem.png", GL_RGB);
}
