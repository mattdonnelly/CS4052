//
//  GLShader.cpp
//  Assignment 3
//
//  Created by Matt Donnelly on 28/10/2014.
//  Copyright (c) 2014 Matt Donnelly. All rights reserved.
//

#include "GLShader.h"
#include <fstream>
#include <assert.h>

GLShader::GLShader(const std::string &shaderCode, GLenum shaderType) : _object(0), _refCount(NULL) {
    // Create the shader object
    _object = glCreateShader(shaderType);
    if (_object == 0) {
        throw std::runtime_error("glCreateShader failed");
    }
    
    // Set the source code
    const char *code = shaderCode.c_str();
    glShaderSource(_object, 1, (const GLchar**)&code, NULL);
    
    // Compile shader
    glCompileShader(_object);
    
    // Throw exception if compilation error occurs
    GLint status;
    glGetShaderiv(_object, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE) {
        std::string msg("Compile failure in shader:\n");
        
        GLint infoLogLength;
        glGetShaderiv(_object, GL_INFO_LOG_LENGTH, &infoLogLength);
        char *strInfoLog = new char[infoLogLength + 1];
        glGetShaderInfoLog(_object, infoLogLength, NULL, strInfoLog);
        msg += strInfoLog;
        delete[] strInfoLog;
        
        glDeleteShader(_object); _object = 0;
        throw std::runtime_error(msg);
    }
    
    _refCount = new unsigned;
    *_refCount = 1;
}

GLShader::~GLShader() {
    if (_refCount) {
        _release();
    }
}

GLShader::GLShader(const GLShader &other) : _object(other._object), _refCount(other._refCount) {
    _retain();
}

GLShader &GLShader::operator = (const GLShader &other) {
    _release();
    _object = other._object;
    _refCount = other._refCount;
    _retain();
    return *this;
}

GLuint GLShader::object() const {
    return _object;
}

GLShader GLShader::shaderFromFile(const std::string filePath, GLenum shaderType) {
    std::ifstream ifile(filePath);
    std::string text;
    
    if (!ifile.is_open()) {
        throw std::runtime_error(std::string("Failed to open file: ") + filePath);
    }
    
    while(ifile.good()) {
        std::string line;
        std::getline(ifile, line);
        text.append(line + "\n");
    }
    
    text += '\0';
    
    GLShader shader(text.c_str(), shaderType);
    return shader;
}

void GLShader::_retain() {
    assert(_refCount);
    *_refCount += 1;
}

void GLShader::_release() {
    assert(_refCount && *_refCount > 0);
    *_refCount -= 1;
    if (*_refCount == 0){
        glDeleteShader(_object); _object = 0;
        delete _refCount; _refCount = NULL;
    }
}