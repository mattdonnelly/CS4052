//
//  PlayerCamera.h
//  Assignment 5
//
//  Created by Matt Donnelly on 04/12/2014.
//  Copyright (c) 2014 Matt Donnelly. All rights reserved.
//

#pragma once

#include "GLCamera.h"
#include "Collidable.h"
#include <glm/glm.hpp>

class Player: public GLCamera, public Collidable {
public:
    Player();
    Player(double fov, double aspect, double near, double far);

    void moveForward(float delta);
    void moveBackward(float delta);

    glm::vec3 collidableLocation() const;
    void collide(Collidable *obj);
};
