//
//  Gem.h
//  Assignment 5
//
//  Created by Matt Donnelly on 06/12/2014.
//  Copyright (c) 2014 Matt Donnelly. All rights reserved.
//

#pragma once

#include "Drawable.h"
#include "Collidable.h"

class Gem : public Drawable, public Collidable {
public:
    Gem(glm::vec3 location);
    
    void draw(GLProgram *shader_program);
    
    glm::vec3 collidableLocation() const;
    int tag();
};
