//
//  Collidable.h
//  Assignment 5
//
//  Created by Matt Donnelly on 07/12/2014.
//  Copyright (c) 2014 Matt Donnelly. All rights reserved.
//

#pragma once

#include <glm/glm.hpp>

class Collidable {
public:
    virtual bool locationWillCollide(glm::vec3 location) const { return false; };
    
    virtual glm::vec3 collidableLocation() const { return glm::vec3(0.0, 0.0, 0.0); };
    virtual void collide(Collidable *obj) {};
    virtual bool isCollidable() { return true; };
    
    virtual int tag() { return -1; };
};
