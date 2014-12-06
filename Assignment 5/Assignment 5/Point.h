//
//  Point.h
//  Assignment 5
//
//  Created by Matt Donnelly on 06/12/2014.
//  Copyright (c) 2014 Matt Donnelly. All rights reserved.
//

#pragma once

#include "Drawable.h"

class Point : public Drawable {
public:
    Point(glm::vec3 location);
    
    static std::vector<Point> generateRandomPoints(const int count);
};
