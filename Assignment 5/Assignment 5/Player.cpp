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
#include <glm/gtc/matrix_transform.hpp>

#define BOUNCE_HEIGHT 0.5
#define BOUNCE_SPEED 5

#define MAX_HEALTH 100.0f

Player::Player(int win_points) : GLCamera(), Animatable() {
    _orig_win_points = win_points;
    _win_points = win_points;
    
    position = glm::vec3(-67.0f, 5.0f, -67.0f);
    forward_direction = glm::vec3(1.0f, 0.0f, 1.0f);
    speed = 15.0f;
    
    regenerating = false;
    
    _health_drain_speed = 5.0f;
    
    _points = 0;
    _health = MAX_HEALTH;
    
    _points_text_id = add_text("Points: 000", 0.55f, -0.8f, 100.0f, 1.0f, 1.0f, 1.0f, 1.0f);
    _health_text_id = add_text("Health: 100", -0.95f, -0.8f, 100.0f, 1.0f, 1.0f, 1.0f, 1.0f);
    
    healthUpSound = AudioManager::sharedManager()->playHealthUp();
}

int Player::points() const {
    return _points;
}

int Player::health() const {
    return _health;
}

bool Player::won() const {
    return _won;
}

bool Player::dead() const {
    return _health < 1;
}

glm::mat4 Player::getViewMatrix() {
    glm::vec3 position_bounce;
    if (_moving) {
        position_bounce = glm::vec3(position.x, position.y + _bounce, position.z);

    }
    else {
        position_bounce = glm::vec3(position.x, position.y, position.z);
    }
    return glm::lookAt(position_bounce, position_bounce + forward_direction, up_direction);
}

void Player::drawText(GLProgram *shader_program) {
    _bounce = fabs(sin(glfwGetTime() * BOUNCE_SPEED) * BOUNCE_HEIGHT);
    
    if (regenerating) {
        update_health(_health + 20.0f * delta());

        if (_health > MAX_HEALTH) {
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
    
    _won = false;
    
    if (fabs(_bounce) < 0.1) {
        _moving = false;
    }
}

void Player::update_position_in_bounds(glm::vec3 new_position) {
    bool collided = false;

    glm::vec3 new_poisitionX = glm::vec3(new_position.x, position.y, position.z);
    for (unsigned i = 0; i < collidables.size(); i++) {
        Collidable *obj = collidables[i];
        
        if (obj->locationWillCollide(new_poisitionX)) {
            collided = true;
        }
    }
    
    if (!collided) {
        position.x = new_position.x;
    }
    
    collided = false;
    
    glm::vec3 new_poisitionZ = glm::vec3(position.x, position.y, new_position.z);
    for (unsigned i = 0; i < collidables.size(); i++) {
        Collidable *obj = collidables[i];
    
        if (obj->locationWillCollide(new_poisitionZ)) {
            collided = true;
        }
    }
    
    if (!collided) {
        position.z = new_position.z;
    }
}

void Player::moveForward(float delta) {
    glm::vec3 new_position = position + (speed * delta * glm::vec3(forward_direction.x, 0.0f, forward_direction.z));

    update_position_in_bounds(new_position);
    _moving = true;
}

void Player::moveBackward(float delta) {
    glm::vec3 new_position = position - (speed * delta * glm::vec3(forward_direction.x, 0.0f, forward_direction.z));
    update_position_in_bounds(new_position);
    _moving = true;
}

void Player::moveLeft(float delta) {
    glm::vec3 new_position = position + (speed * delta * glm::cross(up_direction, forward_direction));
    update_position_in_bounds(new_position);
}

void Player::moveRight(float delta) {
    glm::vec3 new_position = position - (speed * delta * glm::cross(up_direction, forward_direction));
    update_position_in_bounds(new_position);
}

glm::vec3 Player::collidableLocation() const {
    return position;
}

void Player::collide(Collidable *obj) {
    if (obj->tag() == 0) {
        update_points(_points + 1);
        if (_points >= _win_points) {
            _won = true;
            _win_points += _orig_win_points;
            _health_drain_speed += 1.0f;
        }
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
    if (health > 0 && health < MAX_HEALTH + 1) {
        _health = health;
        char tmp[20];
        sprintf(tmp, "Health: %d\n", (int)_health);
        update_text(_health_text_id, tmp);
    }
}

void Player::reset() {
    position = glm::vec3(-67.0f, 5.0f, -67.0f);
    forward_direction = glm::vec3(1.0f, 0.0f, 1.0f);
    update_health(MAX_HEALTH);
    update_points(0);
}
