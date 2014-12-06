//
//  ScoreManager.cpp
//  Assignment 5
//
//  Created by Matt Donnelly on 06/12/2014.
//  Copyright (c) 2014 Matt Donnelly. All rights reserved.
//

#include "ScoreManager.h"
#include "GLProgram.h"
#include "text.h"

ScoreManager::ScoreManager(int width, int height) {
    init_text_rendering("/Users/mattdonnelly/Documents/College/Computer Graphics/Assignment 5/fonts/freemono.png", "/Users/mattdonnelly/Documents/College/Computer Graphics/Assignment 5/fonts/freemono.meta", width, height);
    text_id = add_text("Points: 0",0.4f, -0.8f, 100.0f, 1.0f, 1.0f, 1.0f, 1.0f);
}

void ScoreManager::drawText(GLProgram *shader_program) {
    draw_texts();
    glUseProgram(0);
    glLinkProgram(shader_program->object());
    shader_program->use();
}

void ScoreManager::updateScore(int s) {
    score = s;
    char tmp[8];
    sprintf(tmp, "Points: %06d\n", score);
    update_text(text_id, tmp);
}
