//
//  GLBuffer.h
//  Assignment 3
//
//  Created by Matt Donnelly on 29/10/2014.
//  Copyright (c) 2014 Matt Donnelly. All rights reserved.
//

#pragma once

#include "GLObject.h"

#include <GL/glew.h>
#include <stdio.h>
#include <glm/glm.hpp>

#include "GLProgram.h"

class GLBuffer: public GLObject {
public:
    GLBuffer(GLfloat *data,
             GLint count,
             GLint size,
             GLint stride = 0,
             const GLvoid *offset = 0);

    GLint size() const;
    GLint count() const;
    
private:
    GLint _size;
    GLint _count;
};
