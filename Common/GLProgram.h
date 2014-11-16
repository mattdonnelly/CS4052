//
//  GLProgram.h
//  Assignment 3
//
//  Created by Matt Donnelly on 28/10/2014.
//  Copyright (c) 2014 Matt Donnelly. All rights reserved.
//

#pragma once

#define GLM_FORCE_RADIANS

#include "GLObject.h"

#include <stdio.h>
#include <vector>
#include <glm/glm.hpp>

#include "GLShader.h"

class GLProgram: public GLObject {
public:
    GLProgram(const std::vector<GLShader> &shaders);
    ~GLProgram();
    
    void use() const;
    
    bool isInUse() const;
    
    void stopUsing() const;

    GLint attrib(const GLchar *attribName) const;
    GLint uniform(const GLchar *uniformName) const;

    void setUniform(const GLchar *uniformName, const glm::mat2 &m, GLboolean transpose=GL_FALSE);
    void setUniform(const GLchar *uniformName, const glm::mat3 &m, GLboolean transpose=GL_FALSE);
    void setUniform(const GLchar *uniformName, const glm::mat4 &m, GLboolean transpose=GL_FALSE);
    void setUniform(const GLchar *uniformName, const glm::vec2 &v);
    void setUniform(const GLchar *uniformName, const glm::vec3 &v);
    void setUniform(const GLchar *uniformName, const glm::vec4 &v);
    void setUniform(const GLchar *uniformName, const int value);
    
    void setUniform(const GLint loc, const glm::mat2 &m, GLboolean transpose=GL_FALSE);
    void setUniform(const GLint loc, const glm::mat3 &m, GLboolean transpose=GL_FALSE);
    void setUniform(const GLint loc, const glm::mat4 &m, GLboolean transpose=GL_FALSE);
    void setUniform(const GLint loc, const glm::vec2 &v);
    void setUniform(const GLint loc, const glm::vec3 &v);
    void setUniform(const GLint loc, const glm::vec4 &v);
    void setUniform(const GLint loc, const int value);
};
