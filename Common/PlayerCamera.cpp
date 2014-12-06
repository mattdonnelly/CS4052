//
//  PlayerCamera.cpp
//  Assignment 5
//
//  Created by Matt Donnelly on 04/12/2014.
//  Copyright (c) 2014 Matt Donnelly. All rights reserved.
//

#include "PlayerCamera.h"

PlayerCamera::PlayerCamera() : GLCamera() {
    
}

void PlayerCamera::moveForward(float delta) {
    position += speed * delta * glm::vec3(forward_direction.x, 0.0f, forward_direction.z);
}

void PlayerCamera::moveBackward(float delta) {
    position -= speed * delta * glm::vec3(forward_direction.x, 0.0f, forward_direction.z);
}
