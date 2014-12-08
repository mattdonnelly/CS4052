//
//  PlayerCamera.cpp
//  Assignment 5
//
//  Created by Matt Donnelly on 04/12/2014.
//  Copyright (c) 2014 Matt Donnelly. All rights reserved.
//

#include "Player.h"
#include "text.h"
#include "AudioManager.h"
#include <iostream>

Player::Player() : GLCamera(), Animatable() {
    position = glm::vec3(-67.0f, 5.0f, -67.0f);
    forward_direction = glm::vec3(1.0f, 0.0f, 1.0f);
    speed = 15.0f;
    
    regenerating = false;
    
    _points = 0;
    _health = 100.0f;
    
    _points_text_id = add_text("Points: 000", 0.55f, -0.8f, 100.0f, 1.0f, 1.0f, 1.0f, 1.0f);
    _health_text_id = add_text("Health: 99", -0.95f, -0.8f, 100.0f, 1.0f, 1.0f, 1.0f, 1.0f);
    
    healthUpSound = AudioManager::sharedManager()->playHealthUp();
    healthUpSound->setVolume(0.2);
}

int Player::points() const {
    return _points;
}

int Player::health() const {
    return _health;
}

bool Player::dead() const {
    return _health < 1;
}

void Player::drawText(GLProgram *shader_program) {
    if (regenerating) {
        update_health(_health + 20.0f * delta());

        if (_health > 99) {
            regenerating = false;
            healthUpSound->setIsPaused(true);
            healthUpSound->setPlayPosition(0.0);
        }
    }
    else {
        update_health(_health - 7.0f * delta());
    }

    draw_texts();
    shader_program->use();
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
    if (obj->tag() == 0) {
        update_points(_points + 1);
    }
    else if (obj->tag() == 1) {
        regenerating = true;
        if (healthUpSound->getIsPaused()) {
            healthUpSound->setIsPaused(false);
        }
    }
}

void Player::update_points(int points) {
    _points = points;
    char tmp[20];
    sprintf(tmp, "Points: %03d\n", _points);
    update_text(_points_text_id, tmp);
}

void Player::update_health(double health) {
    if (health > 0 && health < 100) {
        _health = health;
        char tmp[20];
        sprintf(tmp, "Health: %02d\n", (int)_health);
        update_text(_health_text_id, tmp);
    }
}
