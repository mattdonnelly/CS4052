//
//  GLTexture.cpp
//  Assignment 3
//
//  Created by Matt Donnelly on 28/10/2014.
//  Copyright (c) 2014 Matt Donnelly. All rights reserved.
//

#include "GLTexture.h"
#include "stb_image.h"

unsigned int GLTexture::texture_count = 0;

GLTexture::GLTexture(const std::string filepath, GLint format, GLint minMagFiler, GLint wrapMode) {
    unsigned char *pixels = stbi_load(filepath.c_str(), &_width, &_height, &_channels, 0);

    glGenTextures(1, &_object);
    glBindTexture(GL_TEXTURE_2D, _object);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, minMagFiler);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minMagFiler);
    glTexImage2D(GL_TEXTURE_2D, 0, format, (GLsizei)_width, (GLsizei)_height, 0, format, GL_UNSIGNED_BYTE, pixels);
    glBindTexture(GL_TEXTURE_2D, texture_count);
    
    _index = texture_count;
    texture_count++;
    
    delete pixels;
}

GLTexture::~GLTexture() {
    deleteTexture();
}

void GLTexture::bindTexture() const {
    glActiveTexture(GL_TEXTURE0 + _index);
    glBindTexture(GL_TEXTURE_2D, _object);
}

void GLTexture::deleteTexture() const {
    glDeleteTextures(1, &_object);
}

GLint GLTexture::index() const {
    return _index;
}

GLint GLTexture::width() const {
    return _width;
}

GLint GLTexture::height() const {
    return _height;
}

GLint GLTexture::channels() const {
    return _channels;
}

