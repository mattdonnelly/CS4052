//
//  Terrain.cpp
//  Assignment 5
//
//  Created by Matt Donnelly on 06/12/2014.
//  Copyright (c) 2014 Matt Donnelly. All rights reserved.
//

#include "Terrain.h"

Terrain::Terrain() : Drawable(0.0f, 0.0f, 0.0f) {
    vao = Drawable::loadVertexArray("/Users/mattdonnelly/Documents/College/Computer Graphics/Assignment 5/obj/terrain.obj");
    texture = new GLTexture::GLTexture("/Users/mattdonnelly/Documents/College/Computer Graphics/Assignment 5/tex/grass.png", GL_RGB);
}
