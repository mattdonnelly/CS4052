//
//  GLShader.h
//  Assignment 3
//
//  Created by Matt Donnelly on 28/10/2014.
//  Copyright (c) 2014 Matt Donnelly. All rights reserved.
//

#pragma once

#include "GLObject.h"

#include <GL/glew.h>
#include <stdio.h>
#include <string>

class GLShader: public GLObject {
public:
    GLShader(const std::string &shaderCode, GLenum shaderType);
    ~GLShader();
    
    static GLShader shaderFromFile(const std::string filePath, GLenum shaderType);
};
