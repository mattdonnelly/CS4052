//
//  GLProgram.cpp
//  Assignment 3
//
//  Created by Matt Donnelly on 28/10/2014.
//  Copyright (c) 2014 Matt Donnelly. All rights reserved.
//

#include "GLProgram.h"
#include <stdexcept>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

GLProgram::GLProgram(const std::string vertex_shader_path, const std::string frag_shader_path) {
    // Create the program object
    _object = glCreateProgram();
    if (_object == 0) {
        throw std::runtime_error("glCreateProgram failed");
    }
    
    GLShader vertex_shader = GLShader::shaderFromFile(vertex_shader_path, GL_VERTEX_SHADER);
    GLShader frag_shader = GLShader::shaderFromFile(frag_shader_path, GL_FRAGMENT_SHADER);
    
    // Attach all the shaders
    glAttachShader(_object, vertex_shader.object());
    glAttachShader(_object, frag_shader.object());
    
    // Link the shaders
    glLinkProgram(_object);
    
    // Detach all the shaders
    glDetachShader(_object, vertex_shader.object());
    glDetachShader(_object, frag_shader.object());

    // Throw exception if linking fails
    GLint status;
    glGetProgramiv(_object, GL_LINK_STATUS, &status);
    if (status == GL_FALSE) {
        std::string msg("Program linking failure: ");
        
        GLint infoLogLength;
        glGetProgramiv(_object, GL_INFO_LOG_LENGTH, &infoLogLength);
        char *strInfoLog = new char[infoLogLength + 1];
        glGetProgramInfoLog(_object, infoLogLength, NULL, strInfoLog);
        msg += strInfoLog;
        delete[] strInfoLog;
        
        glDeleteProgram(_object);
        _object = 0;
        throw std::runtime_error(msg);
    }
    
    glUseProgram(_object);
}

void GLProgram::use() const {
    glUseProgram(_object);
}

bool GLProgram::isInUse() const {
    GLint currentProgram = 0;
    glGetIntegerv(GL_CURRENT_PROGRAM, &currentProgram);
    return (currentProgram == (GLint)_object);
}

void GLProgram::stopUsing() const {
    glUseProgram(0);
}

GLint GLProgram::attrib(const GLchar *attribName) const {
    if (!attribName) {
        throw std::runtime_error("attribName was NULL");
    }
    
    GLint attrib = glGetAttribLocation(_object, attribName);
    if (attrib == -1) {
        throw std::runtime_error(std::string("Program attribute not found: ") + attribName);
    }
    
    return attrib;
}

GLint GLProgram::uniform(const GLchar *uniformName) const {
    if(!uniformName) {
        throw std::runtime_error("uniformName was NULL");
    }
    
    GLint uniform = glGetUniformLocation(_object, uniformName);
    if (uniform == -1) {
        throw std::runtime_error(std::string("Program uniform not found: ") + uniformName);
    }

    return uniform;
}

void GLProgram::setUniform(const GLchar *name, const glm::mat2 &m, GLboolean transpose) {
    assert(isInUse());
    glUniformMatrix2fv(uniform(name), 1, transpose, glm::value_ptr(m));
}

void GLProgram::setUniform(const GLchar *name, const glm::mat3 &m, GLboolean transpose) {
    assert(isInUse());
    glUniformMatrix3fv(uniform(name), 1, transpose, glm::value_ptr(m));
}

void GLProgram::setUniform(const GLchar *name, const glm::mat4 &m, GLboolean transpose) {
    assert(isInUse());
    glUniformMatrix4fv(uniform(name), 1, transpose, glm::value_ptr(m));
}

void GLProgram::setUniform(const GLchar *name, const glm::vec2 &v) {
    assert(isInUse());
    glUniform2fv(uniform(name), 1, glm::value_ptr(v));
}

void GLProgram::setUniform(const GLchar *name, const glm::vec3 &v) {
    assert(isInUse());
    glUniform3fv(uniform(name), 1, glm::value_ptr(v));
}

void GLProgram::setUniform(const GLchar *name, const glm::vec4& v) {
    assert(isInUse());
    glUniform4fv(uniform(name), 1, glm::value_ptr(v));
}

void GLProgram::setUniform(const GLchar *name, const double v) {
    assert(isInUse());
    glUniform1d(uniform(name), v);
}

void GLProgram::setUniform(const GLchar *name, const float v) {
    assert(isInUse());
    glUniform1f(uniform(name), v);
}

void GLProgram::setUniform(const GLchar *name, const int v) {
    assert(isInUse());
    glUniform1i(uniform(name), v);
}

void GLProgram::setUniform(const GLint loc, const glm::mat2 &m, GLboolean transpose) {
    assert(isInUse());
    glUniformMatrix2fv(loc, 1, transpose, glm::value_ptr(m));
}

void GLProgram::setUniform(const GLint loc, const glm::mat3 &m, GLboolean transpose) {
    assert(isInUse());
    glUniformMatrix3fv(loc, 1, transpose, glm::value_ptr(m));
}

void GLProgram::setUniform(const GLint loc, const glm::mat4 &m, GLboolean transpose) {
    assert(isInUse());
    glUniformMatrix4fv(loc, 1, transpose, glm::value_ptr(m));
}

void GLProgram::setUniform(const GLint loc, const glm::vec2 &v) {
    assert(isInUse());
    glUniform2fv(loc, 1, glm::value_ptr(v));
}

void GLProgram::setUniform(const GLint loc, const glm::vec3 &v) {
    assert(isInUse());
    glUniform3fv(loc, 1, glm::value_ptr(v));
}

void GLProgram::setUniform(const GLint loc, const glm::vec4& v) {
    assert(isInUse());
    glUniform4fv(loc, 1, glm::value_ptr(v));
}

void GLProgram::setUniform(const GLint loc, const double v) {
    assert(isInUse());
    glUniform1d(loc, v);
}

void GLProgram::setUniform(const GLint loc, const float v) {
    assert(isInUse());
    glUniform1f(loc, v);
}

void GLProgram::setUniform(const GLint loc, const int v) {
    assert(isInUse());
    glUniform1i(loc, v);
}
