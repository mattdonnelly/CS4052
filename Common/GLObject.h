//
//  GLObject.h
//  Assignment 4
//
//  Created by Matt Donnelly on 16/11/2014.
//  Copyright (c) 2014 Matt Donnelly. All rights reserved.
//

#pragma once

#include <GL/glew.h>

class GLObject {
public:
    GLuint object() const;
    
protected:
    GLuint _object;
};

