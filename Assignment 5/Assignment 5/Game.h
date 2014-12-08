//
//  Game.h
//  Assignment 5
//
//  Created by Matt Donnelly on 08/12/2014.
//  Copyright (c) 2014 Matt Donnelly. All rights reserved.
//

#pragma once

#include "Window.h"
#include "Point.h"
#include "Gem.h"
#include "Terrain.h"
#include "CollisionManager.h"
#include "GLProgram.h"

class Game {
public:
    Game();
    
    void start();
    void reset();
    
private:
    Window *window;
    
    Player *player;
    Terrain *terrain;
    Gem *gem1;
    Gem *gem2;
    std::vector<Point *> points;
    
    CollisionManager *point_collision_manager;
    CollisionManager *gem_collision_manager;
    
    GLProgram *shader_program;
    
    void init();
};