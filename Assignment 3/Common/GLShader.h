//
//  GLShader.h
//  Assignment 3
//
//  Created by Matt Donnelly on 28/10/2014.
//  Copyright (c) 2014 Matt Donnelly. All rights reserved.
//

#pragma once

#include <GL/glew.h>
#include <stdio.h>
#include <string>

class GLShader {
public:
    static GLShader shaderFromFile(const std::string filePath, GLenum shaderType);
    
    GLShader(const std::string &shaderCode, GLenum shaderType);
    ~GLShader();
    
    GLShader(const GLShader &other);
    GLShader &operator =(const GLShader &other);

    GLuint object() const;
    
private:
    GLuint _object;

    unsigned* _refCount;
    
    void _retain();
    void _release();
};
