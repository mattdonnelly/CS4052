//
//  GLBuffer.h
//  Assignment 3
//
//  Created by Matt Donnelly on 29/10/2014.
//  Copyright (c) 2014 Matt Donnelly. All rights reserved.
//

#pragma once

#include <GL/glew.h>
#include <stdio.h>
#include <glm/glm.hpp>

#include "GLProgram.h"

class GLBuffer {
public:
    GLBuffer();
    ~GLBuffer();
    
    void bufferObject(GLfloat *data,
                      GLint size,
                      GLint count,
                      GLint stride = 0,
                      const GLvoid *offset = 0);
    
    GLuint object() const;
    
private:
    GLuint _object;
    unsigned attribCount;
};
