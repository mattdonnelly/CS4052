//
//  GLBuffer.cpp
//  Assignment 3
//
//  Created by Matt Donnelly on 29/10/2014.
//  Copyright (c) 2014 Matt Donnelly. All rights reserved.
//

#include "GLBuffer.h"

GLBuffer::GLBuffer() {
    glGenVertexArrays(1, &_object);
    glBindVertexArray(_object);
    attribCount = 0;
}

GLBuffer::~GLBuffer() {
    glDeleteVertexArrays(1, &_object);
}

void GLBuffer::bufferObject(GLfloat *data, GLint size, GLint count, GLint stride, const GLvoid * pointer) {
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, count, data, GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(attribCount);
    glVertexAttribPointer(attribCount, size, GL_FLOAT, GL_FALSE, 0, 0);
    attribCount++;
}

GLuint GLBuffer::object() const {
    return _object;
}
