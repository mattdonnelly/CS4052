//
//  Game.cpp
//  Assignment 5
//
//  Created by Matt Donnelly on 08/12/2014.
//  Copyright (c) 2014 Matt Donnelly. All rights reserved.
//

#include "Game.h"
#include "AudioManager.h"
#include "LightSource.h"

#define FPS 60

#define NUM_POINTS 8
#define NUM_TREES 20

Game::Game() {
    window = new Window("Assignment 5", 1280, 720);
    
    player = new Player(NUM_POINTS);
    window->camera = player;

    terrain = new Terrain();

    trees = Tree::generateRandomTrees(NUM_TREES, -67, 67);

    player->collidables.push_back(terrain);
    player->collidables.insert(player->collidables.end(), trees.begin(), trees.end());
    
    shader_program = new GLProgram("/Users/mattdonnelly/Documents/College/Computer Graphics/Assignment 5/Assignment 5/vertex_shader.glsl", "/Users/mattdonnelly/Documents/College/Computer Graphics/Assignment 5/Assignment 5/fragment_shader.glsl");
    
    init();
}

void Game::init() {
    gem1 = new Gem(glm::vec3( 70.0f, 4.0f,  70.f));
    gem2 = new Gem(glm::vec3(-70.0f, 4.0f, -70.f));

    std::vector<Collidable *> collidable_gems;
    collidable_gems.push_back(gem1);
    collidable_gems.push_back(gem2);
    
    gem_collision_manager = new DistanceManager();
    gem_collision_manager->main_object = player;
    gem_collision_manager->addCollidables(collidable_gems);
    
    next_wave();
}

void Game::next_wave() {
    points = Point::generateRandomPoints(NUM_POINTS, -70, 70);
    std::vector<Collidable *> collidable_points(points.begin(), points.end());
    
    point_collision_manager = new DistanceManager();
    point_collision_manager->main_object = player;
    point_collision_manager->addCollidables(collidable_points);
}

void Game::reset() {
    delete gem1;
    delete gem2;
    delete point_collision_manager;
    delete gem_collision_manager;
    player->reset();
    
    init();
}

void Game::start() {
    const int view_mat_location = shader_program->uniform("view");

    AudioManager::sharedManager()->playMusic();
    
    shader_program->use();
    window->setShaderProgram(shader_program);
    
    double last_tick = window->getTime();

    while (!window->shouldClose()) {
        window->clear();
        
        glm::mat4 view = player->getViewMatrix();
        shader_program->setUniform(view_mat_location, view);
        
        terrain->draw(shader_program);
        
        for (int i = 0; i < NUM_TREES; i++) {
            trees[i]->draw(shader_program);
        }
        
        gem1->draw(shader_program);
        gem2->draw(shader_program);

        for (int i = 0; i < NUM_POINTS; i++) {
            points[i]->draw(shader_program);
        }
        
        player->drawText(shader_program);
        
        point_collision_manager->checkCollisions();
        gem_collision_manager->checkCollisions();
        
        if (player->dead()) {
            AudioManager::sharedManager()->playGameOver();
            reset();
        }
        else if (player->won()) {
            next_wave();
            AudioManager::sharedManager()->playWon();
        }
        
        window->pollEvents();
        window->swapBuffers();
        
        while (window->getTime() < last_tick + 1 / FPS);
        last_tick = window->getTime();
    }
    
    glfwTerminate();
}
