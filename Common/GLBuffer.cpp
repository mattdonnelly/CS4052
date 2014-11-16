//
//  GLBuffer.cpp
//  Assignment 3
//
//  Created by Matt Donnelly on 29/10/2014.
//  Copyright (c) 2014 Matt Donnelly. All rights reserved.
//

#include "GLBuffer.h"

GLBuffer::GLBuffer(GLfloat *data, GLint count, GLint size, GLint stride, const GLvoid *offset) {
    _size = size;
    _count = count;
    
    glGenBuffers(1, &_object);
    glBindBuffer(GL_ARRAY_BUFFER, _object);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

GLint GLBuffer::size() const {
    return _size;
}

GLint GLBuffer::count() const {
    return _count;
}
