//
//  Point.h
//  Assignment 5
//
//  Created by Matt Donnelly on 06/12/2014.
//  Copyright (c) 2014 Matt Donnelly. All rights reserved.
//

#pragma once

#include "Drawable.h"
#include "Collidable.h"

class Point : public Drawable, public Collidable {
public:
    Point(glm::vec3 location);
    
    static std::vector<Point *> generateRandomPoints(const int count);
    
    void draw(GLProgram shader_program);

    glm::vec3 collidableLocation() const;
    void collide(Collidable *obj);
    
private:
    bool collected;
};
