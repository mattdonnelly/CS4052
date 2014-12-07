//
//  GLVertexArray.h
//  Assignment 4
//
//  Created by Matt Donnelly on 16/11/2014.
//  Copyright (c) 2014 Matt Donnelly. All rights reserved.
//

#pragma once

#include "GLObject.h"
#include "GLBuffer.h"

#include <vector>

class GLVertexArray: public  GLObject {
public:
    GLVertexArray(const char *filename);
    ~GLVertexArray();
    
    void draw() const;
    
    GLint point_count() const;

private:
    GLint _point_count;
};
