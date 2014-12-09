//
//  CollisionManager.cpp
//  Assignment 5
//
//  Created by Matt Donnelly on 07/12/2014.
//  Copyright (c) 2014 Matt Donnelly. All rights reserved.
//

#include "DistanceManager.h"
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

DistanceManager::DistanceManager() {
    
}

void DistanceManager::addCollidable(Collidable *c) {
    _collidables.push_back(c);
}

void DistanceManager::addCollidables(std::vector<Collidable *> collidables) {
    _collidables.insert(_collidables.end(), collidables.begin(), collidables.end());
}

bool DistanceManager::checkCollisions() {
    bool collided = false;

    for (unsigned i = 0; i < _collidables.size(); i++) {
        Collidable *obj = _collidables[i];
        
        if (main_object->isCollidable() && obj->isCollidable()) {
            if (obj->locationWillCollide(main_object->collidableLocation())) {
                main_object->collide(obj);
                obj->collide(main_object);
                collided = true;
            }
        }
    }
    
    return collided;
}
