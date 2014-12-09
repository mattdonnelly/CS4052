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

class DistanceManager {
public:
    DistanceManager();

    Collidable *main_object;
    void addCollidable(Collidable *c);
    void addCollidables(std::vector<Collidable *> collidables);

    bool checkCollisions();

private:
    std::vector<Collidable *> _collidables;
};
