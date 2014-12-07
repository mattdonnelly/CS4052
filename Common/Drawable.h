//
//  Drawable.h
//  Assignment 5
//
//  Created by Matt Donnelly on 06/12/2014.
//  Copyright (c) 2014 Matt Donnelly. All rights reserved.
//

#pragma once

#define STB_IMAGE_IMPLEMENTATION
#define GLM_FORCE_RADIANS

#include <stdio.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "GLVertexArray.h"
#include "GLTexture.h"
#include "GLProgram.h"
#include "obj_parser.h"

class Drawable {
public:
    Drawable(double x, double y, double z);
    Drawable(glm::vec3 location);

    glm::vec3 location;
    glm::vec3 scale;
    
    GLVertexArray *vao;
    GLTexture *texture;
    
    virtual void draw(GLProgram shader_program);
    
    GLVertexArray *loadVertexArray(const char *file_name);
};
