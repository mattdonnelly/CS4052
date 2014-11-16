//
//  GLVertexArray.cpp
//  Assignment 4
//
//  Created by Matt Donnelly on 16/11/2014.
//  Copyright (c) 2014 Matt Donnelly. All rights reserved.
//

#include "GLVertexArray.h"

GLVertexArray::GLVertexArray(std::vector<GLBuffer> buffers) {
    glGenVertexArrays (1, &_object);
    glBindVertexArray(_object);
    
    for (unsigned i = 0; i < buffers.size(); ++i) {
        GLBuffer buffer = buffers[i];
        glBindBuffer(GL_ARRAY_BUFFER, buffer.object());
        glVertexAttribPointer(i, buffer.count(), GL_FLOAT, GL_FALSE, 0, NULL);
    }
    
    for (unsigned i = 0; i < buffers.size(); ++i) {
        glEnableVertexAttribArray(i);
    }
}

GLVertexArray::~GLVertexArray() {
    glDeleteVertexArrays(1, &_object);
}

void GLVertexArray::bind() const {
    glBindVertexArray(_object);
}
