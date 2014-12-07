//
//  CollisionManager.cpp
//  Assignment 5
//
//  Created by Matt Donnelly on 07/12/2014.
//  Copyright (c) 2014 Matt Donnelly. All rights reserved.
//

#include "CollisionManager.h"
#include <glm/glm.hpp>
#include <iostream>

CollisionManager::CollisionManager() {
    
}

void CollisionManager::addCollidable(Collidable *c) {
    _collidables.push_back(c);
}

void CollisionManager::addCollidables(std::vector<Collidable *> collidables) {
    _collidables.insert(_collidables.end(), collidables.begin(), collidables.end());
}

void CollisionManager::checkCollisions(double delta) {
    for (unsigned i = 0; i < _collidables.size(); i++) {
        Collidable *obj = _collidables[i];
        
        float dist = glm::distance(main_object->collidableLocation(), obj->collidableLocation());
        if (dist <= delta) {
            main_object->collide(obj);
            obj->collide(main_object);
        }
    }
}
