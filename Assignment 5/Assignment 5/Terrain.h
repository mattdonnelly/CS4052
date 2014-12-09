//
//  Terrain.h
//  Assignment 5
//
//  Created by Matt Donnelly on 06/12/2014.
//  Copyright (c) 2014 Matt Donnelly. All rights reserved.
//

#pragma once

#include "Drawable.h"
#include "Collidable.h"
#include "LightSource.h"

class Terrain : public Drawable, public Collidable {
public:
    Terrain();
    
    void draw(GLProgram *shader_program);

    bool locationWillCollide(glm::vec3 location) const;
    
private:
    LightSource light;
};
