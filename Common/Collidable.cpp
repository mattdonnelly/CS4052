//
//  Collidable.h
//  Assignment 5
//
//  Created by Matt Donnelly on 07/12/2014.
//  Copyright (c) 2014 Matt Donnelly. All rights reserved.
//

#include "Collidable.h"

bool Collidable::locationWillCollide(glm::vec3 location) const {
    return false;
}

glm::vec3 Collidable::collidableLocation() const {
    return glm::vec3(0.0, 0.0, 0.0);
}

void Collidable::collide(Collidable *obj) {

}

bool Collidable::isCollidable() {
    return true;
}

int Collidable::tag() {
    return -1;
}
