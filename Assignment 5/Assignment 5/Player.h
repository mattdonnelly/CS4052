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

class Player: public GLCamera, public Animatable, public Collidable {
public:
    Player(int win_points);

    glm::mat4 getViewMatrix();
    void drawText(GLProgram *shader_program);
    
    int points() const;
    int health() const;
    
    bool won() const;
    bool dead() const;

    void update_points(int score);
    void update_health(double health);
    void reset();

    void moveForward(float delta);
    void moveBackward(float delta);
    void moveLeft(float delta);
    void moveRight(float delta);

    std::vector<Collidable *> collidables;
    glm::vec3 collidableLocation() const;
    void collide(Collidable *obj);

private:
    irrklang::ISound *healthUpSound;
    
    bool _moving;
    double _bounce;
    
    int _orig_win_points;
    int _win_points;
    bool _won;
    
    void update_position_in_bounds(glm::vec3 new_position);
    
    int _points;
    int _points_text_id;

    double _health;
    int _health_text_id;
    
    bool regenerating;
};
