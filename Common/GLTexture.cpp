//
//  GLTexture.cpp
//  Assignment 3
//
//  Created by Matt Donnelly on 28/10/2014.
//  Copyright (c) 2014 Matt Donnelly. All rights reserved.
//

#include "GLTexture.h"

#include <IL/il.h>

GLTexture::GLTexture(const std::string filepath, GLint minMagFilter, GLint wrapMode) {
    GLuint imageID;
    ilInit();
    ilGenImages(1, &imageID);
    ilBindImage(imageID);
    ilEnable(IL_ORIGIN_SET);
    ilOriginFunc(IL_ORIGIN_LOWER_LEFT);

    if (ilLoadImage(filepath.c_str()) == IL_FALSE) {
        
    }

    ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);

    _width = ilGetInteger(IL_IMAGE_WIDTH);
    _height = ilGetInteger(IL_IMAGE_HEIGHT);
    
    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &_object);
    glBindTexture(GL_TEXTURE_2D, _object);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, minMagFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minMagFilter);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, ilGetData());
    glGenerateMipmap(GL_TEXTURE_2D);
    
    ilShutDown();
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

