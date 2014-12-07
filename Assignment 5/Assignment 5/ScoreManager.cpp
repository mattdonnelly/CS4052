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
    text_id = add_text("Points: 000", 0.55f, -0.8f, 100.0f, 1.0f, 1.0f, 1.0f, 1.0f);
}

void ScoreManager::drawText(GLProgram *shader_program) {
    draw_texts();
    shader_program->use();
    glDisable(GL_BLEND);
}

void ScoreManager::updateScore(int s) {
    if (score != s) {
        score = s;
        char tmp[20];
        sprintf(tmp, "Points: %03d\n", score);
        update_text(text_id, tmp);
    }
}
