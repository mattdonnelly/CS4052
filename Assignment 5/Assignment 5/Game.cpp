//
//  Game.cpp
//  Assignment 5
//
//  Created by Matt Donnelly on 08/12/2014.
//  Copyright (c) 2014 Matt Donnelly. All rights reserved.
//

#include "Game.h"
#include "AudioManager.h"

#define NUM_POINTS 8
#define FPS 60

const glm::vec3 world_light_position = glm::vec3(0, 15.0f, 0.0f);
const glm::vec3 gem1_position = glm::vec3( 70.0f, 4.0f,  70.f);
const glm::vec3 gem2_position = glm::vec3(-70.0f, 4.0f, -70.f);

Game::Game() {
    window = new Window("Assignment 5", 1280, 720);
    
    player = new Player(NUM_POINTS, -75.0f, -75.0f, 75.0f, 75.0f);
    window->camera = player;

    terrain = new Terrain();
    
    shader_program = new GLProgram("/Users/mattdonnelly/Documents/College/Computer Graphics/Assignment 5/Assignment 5/vertex_shader.glsl", "/Users/mattdonnelly/Documents/College/Computer Graphics/Assignment 5/Assignment 5/fragment_shader.glsl");
    
    init();
}

void Game::init() {
    gem1 = new Gem(gem1_position);
    gem2 = new Gem(gem2_position);

    std::vector<Collidable *> collidable_gems;
    collidable_gems.push_back(gem1);
    collidable_gems.push_back(gem2);
    
    gem_collision_manager = new CollisionManager();
    gem_collision_manager->main_object = player;
    gem_collision_manager->addCollidables(collidable_gems);
    
    next_wave();
}

void Game::next_wave() {
    points = Point::generateRandomPoints(NUM_POINTS, -70, 70);
    std::vector<Collidable *> collidable_points(points.begin(), points.end());
    
    point_collision_manager = new CollisionManager();
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
    
    const int light_position_world_location = shader_program->uniform("light_position_world");
    const int light_position_gem1_location = shader_program->uniform("light_position_gem1");
    const int light_position_gem2_location = shader_program->uniform("light_position_gem2");
    
    const int light_properties_world_location = shader_program->uniform("light_properties_world");
    const int light_properties_gem_location = shader_program->uniform("light_properties_gem");
    
    glm::mat3 light_properties_world = glm::mat3(0.7, 0.9, 0.9,
                                                 0.5, 0.7, 0.5,
                                                 0.1, 0.2, 0.2);
    
    AudioManager::sharedManager()->playMusic();
    
    shader_program->use();
    window->setShaderProgram(shader_program);
    
    double last_tick = window->getTime();

    while (!window->shouldClose()) {
        window->clear();
        
        glm::mat4 view = player->getViewMatrix();
        shader_program->setUniform(view_mat_location, view);
        
        terrain->draw(shader_program);
        
        shader_program->setUniform(light_position_world_location, world_light_position);
        shader_program->setUniform(light_position_gem1_location, gem1_position);
        shader_program->setUniform(light_position_gem2_location, gem2_position);
        
        double oscillation = fabs(sinf(window->getTime()));
        
        glm::mat3 light_properties_gem = glm::mat3(1.0, 1.0, 1.0,
                                                   3.0f + (5.0f * oscillation), 0.0, 0.0,
                                                   0.0, 0.0, 0.0);
        
        shader_program->setUniform(light_properties_world_location, light_properties_world);
        shader_program->setUniform(light_properties_gem_location, light_properties_gem);
        
        gem1->draw(shader_program);
        gem2->draw(shader_program);
        
        player->drawText(shader_program);
        
        for (int i = 0; i < NUM_POINTS; i++) {
            points[i]->draw(shader_program);
        }
        
        point_collision_manager->checkCollisions(3.0f);
        gem_collision_manager->checkCollisions(18.0f);
        
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
        
        while(window->getTime() < last_tick+1/FPS);
        last_tick = window->getTime();
    }
    
    glfwTerminate();
}
