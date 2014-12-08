//
//  PlayerCamera.h
//  Assignment 5
//
//  Created by Matt Donnelly on 04/12/2014.
//  Copyright (c) 2014 Matt Donnelly. All rights reserved.
//

#pragma once

#include "GLCamera.h"
#include "GLProgram.h"
#include "Collidable.h"
#include "Animatable.h"
#include <irrKlang.h>

#include <glm/glm.hpp>

class Window;

class Player: public GLCamera, public Animatable, public Collidable {
public:
    Player(Window window);

    void drawText(GLProgram shader_program);
    
    int points() const;

    void moveForward(float delta);
    void moveBackward(float delta);

    glm::vec3 collidableLocation() const;
    void collide(Collidable *obj);
    
private:
    irrklang::ISound *healthUpSound;
    
    int _points;
    int _points_text_id;

    double _health;
    int _health_text_id;
    
    bool regenerating;
    
    void update_points(int score);
    void update_health(double health);
};
