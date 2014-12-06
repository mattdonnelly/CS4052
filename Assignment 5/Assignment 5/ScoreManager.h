//
//  ScoreManager.h
//  Assignment 5
//
//  Created by Matt Donnelly on 06/12/2014.
//  Copyright (c) 2014 Matt Donnelly. All rights reserved.
//

#pragma once

#include "GLProgram.h"

class GLProgram;

class ScoreManager {
public:
    ScoreManager(int width, int height);
    
    int score = 0;
    
    void drawText(GLProgram *shader_program);
    
    void updateScore(int score);

private:
    int text_id;
    char *text;
};
