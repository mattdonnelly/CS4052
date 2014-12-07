//
//  CollisionManager.h
//  Assignment 5
//
//  Created by Matt Donnelly on 07/12/2014.
//  Copyright (c) 2014 Matt Donnelly. All rights reserved.
//

#pragma once

#include "Drawable.h"
#include "Collidable.h"

class CollisionManager {
public:
    CollisionManager();
    
    Collidable *main_object;
    void addCollidable(Collidable *c);
    void addCollidables(std::vector<Collidable *> collidables);

    void checkCollisions(double delta);

private:
    std::vector<Collidable *> _collidables;
};
