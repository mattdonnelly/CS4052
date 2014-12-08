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

class Terrain : public Drawable, public Collidable {
public:
    Terrain();
    
    bool locationWillCollide(glm::vec3 location) const;
};
