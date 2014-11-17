//
//  GLTexture.h
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

class GLTexture: public GLObject {
public:
    GLTexture(const std::string filepath,
              GLint format,
              GLint minMagFiler = GL_LINEAR,
              GLint wrapMode = GL_REPEAT);
    ~GLTexture();

    static unsigned int texture_count;
    
    void bindTexture(GLint slot) const;
    void deleteTexture() const;
    
    GLint index() const;
    GLint width() const;
    GLint height() const;
    GLint channels() const;
    
private:
    GLint _index;
    GLint _width;
    GLint _height;
    GLint _channels;

    const GLTexture &operator=(const GLTexture&);
};
