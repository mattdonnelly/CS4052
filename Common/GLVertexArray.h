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
    GLVertexArray(const std::vector<GLBuffer> &buffers);
    ~GLVertexArray();
    
    void bind() const;

private:
    std::vector<GLBuffer> _buffers;
};
