//
//  GLVertexArray.cpp
//  Assignment 4
//
//  Created by Matt Donnelly on 16/11/2014.
//  Copyright (c) 2014 Matt Donnelly. All rights reserved.
//

#include "GLVertexArray.h"

GLVertexArray::GLVertexArray(const std::vector<GLBuffer> &buffers) {
    if (buffers.size() <= 0) {
        throw std::runtime_error("Must pass at least one shader to create program");
    }
    
    _buffers = buffers;
    
    // Create the vertex array object
    glGenVertexArrays (1, &_object);
    if (_object == 0) {
        throw std::runtime_error("glGenVertexArrays failed");
    }

    glBindVertexArray(_object);

    // Bind buffers
    for (unsigned i = 0; i < buffers.size(); ++i) {
        GLBuffer buffer = buffers[i];
        glBindBuffer(GL_ARRAY_BUFFER, buffer.object());
        glVertexAttribPointer(i, buffer.count(), GL_FLOAT, GL_FALSE, 0, NULL);
        glEnableVertexAttribArray(i);
    }
}

GLVertexArray::~GLVertexArray() {
    for (unsigned i = 0; i < _buffers.size(); ++i) {
        GLuint obj = _buffers[i].object();
        glDeleteBuffers(1, &obj);
    }
    
    glDeleteVertexArrays(1, &_object);
}

void GLVertexArray::bind() const {
    glBindVertexArray(_object);
}
