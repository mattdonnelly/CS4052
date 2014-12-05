//
//  GLTexture.cpp
//  Assignment 3
//
//  Created by Matt Donnelly on 28/10/2014.
//  Copyright (c) 2014 Matt Donnelly. All rights reserved.
//

#include <mutex>

#include "GLTexture.h"
#include "stb_image.h"

std::mutex mtx;

GLTexture::GLTexture(const std::string filepath, GLint format, GLint minMagFiler, GLint wrapMode) {
    unsigned char *pixels = stbi_load(filepath.c_str(), &_width, &_height, &_channels, 0);

    printf("%d\n", _width);
    printf("%d\n", _height);
    
    glGenTextures(1, &_object);
    glBindTexture(GL_TEXTURE_2D, _object);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, minMagFiler);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minMagFiler);
    glTexImage2D(GL_TEXTURE_2D, 0, format, (GLsizei)_width, (GLsizei)_height, 0, format, GL_UNSIGNED_BYTE, pixels);
    
    stbi_image_free(pixels);
}

GLTexture::~GLTexture() {
    glDeleteTextures(1, &_object);
}

void GLTexture::bindTexture(GLint slot) const {
    glActiveTexture(slot);
    glBindTexture(GL_TEXTURE_2D, _object);
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

