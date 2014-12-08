//
//  Tree.h
//  Assignment 5
//
//  Created by Matt Donnelly on 08/12/2014.
//  Copyright (c) 2014 Matt Donnelly. All rights reserved.
//

#pragma once

#include "Drawable.h"
#include "Collidable.h"

class Tree : public Drawable, public Collidable {
public:
    Tree(glm::vec3 location);
    
    static std::vector<Tree *> generateRandomTrees(const int count, int min, int max);

    bool locationWillCollide(glm::vec3 location) const;
};
