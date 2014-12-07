//
//  PlayerCamera.cpp
//  Assignment 5
//
//  Created by Matt Donnelly on 04/12/2014.
//  Copyright (c) 2014 Matt Donnelly. All rights reserved.
//

#include "Player.h"

Player::Player() : GLCamera() {
    
}

void Player::moveForward(float delta) {
    position += speed * delta * glm::vec3(forward_direction.x, 0.0f, forward_direction.z);
}

void Player::moveBackward(float delta) {
    position -= speed * delta * glm::vec3(forward_direction.x, 0.0f, forward_direction.z);
}

glm::vec3 Player::collidableLocation() const {
    return position;
}

void Player::collide(Collidable *obj) {
    
}
