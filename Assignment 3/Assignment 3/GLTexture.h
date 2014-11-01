//
//  GLTexture.h
//  Assignment 3
//
//  Created by Matt Donnelly on 28/10/2014.
//  Copyright (c) 2014 Matt Donnelly. All rights reserved.
//

#pragma once

#include <GL/glew.h>
#include <stdio.h>
#include <string>

class GLTexture {
public:
    GLTexture(const std::string filepath,
              GLint format,
              GLint minMagFiler = GL_LINEAR,
              GLint wrapMode = GL_CLAMP_TO_EDGE);
    ~GLTexture();

    GLuint object() const;
    void bindTexture() const;
    
    GLint width() const;
    GLint height() const;
    GLint channels() const;
    
private:
    GLuint _object;
    GLint _width;
    GLint _height;
    GLint _channels;

    const GLTexture &operator=(const GLTexture&);
};
