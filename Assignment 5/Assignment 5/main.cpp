//
//  main.cpp
//  Assignment 5
//
//  Created by Matt Donnelly on 09/11/2014.
//  Copyright (c) 2014 Matt Donnelly. All rights reserved.
//

#define GLM_FORCE_RADIANS

#include <iostream>

#include "Player.h"
#include "ScoreManager.h"
#include "CollisionManager.h"
#include "AudioManager.h"
#include "GLProgram.h"
#include "Window.h"

#include "Terrain.h"
#include "Gem.h"
#include "Point.h"

#define NUM_POINTS 15

#define FPS 60.0

int main(int argc, const char * argv[]) {
    Window window = Window("Assignment 5", 1280, 720);
    
    GLProgram shader_program = GLProgram("/Users/mattdonnelly/Documents/College/Computer Graphics/Assignment 5/Assignment 5/vertex_shader.glsl", "/Users/mattdonnelly/Documents/College/Computer Graphics/Assignment 5/Assignment 5/fragment_shader.glsl");

    Terrain terrain = Terrain();
    
    const glm::vec3 world_light_position = glm::vec3(0, 15.0f, 0.0f);
    const glm::vec3 gem1_position = glm::vec3( 70.0f, 4.0f,  70.f);
    const glm::vec3 gem2_position = glm::vec3(-70.0f, 4.0f, -70.f);
    
    Gem gem1 = Gem(gem1_position);
    Gem gem2 = Gem(gem2_position);
    
    std::vector<Point *> points = Point::generateRandomPoints(NUM_POINTS);

    Player player = Player();
    window.player = &player;
    
    const int view_mat_location = shader_program.uniform("view");
    
    const int light_position_world_location = shader_program.uniform("light_position_world");
    const int light_position_gem1_location = shader_program.uniform("light_position_gem1");
    const int light_position_gem2_location = shader_program.uniform("light_position_gem2");

    const int light_properties_world_location = shader_program.uniform("light_properties_world");
    const int light_properties_gem_location = shader_program.uniform("light_properties_gem");
    
    glm::mat3 light_properties_world = glm::mat3(0.7, 0.9, 0.9,
                                                 0.5, 0.7, 0.5,
                                                 0.1, 0.2, 0.2);
    
    ScoreManager score_manager = ScoreManager(window.width, window.height);
    
    std::vector<Collidable *> collidable_point(points.begin(), points.end());
    
    CollisionManager collision_manager = CollisionManager();
    collision_manager.main_object = &player;
    collision_manager.addCollidables(collidable_point);
    
    AudioManager::sharedManager()->playMusic();

    shader_program.use();
    window.setShaderProgram(&shader_program);
    
    double last_tick = window.getTime();
    
    while (!window.shouldClose()) {
        window.clear();
        
        glm::mat4 view = player.getViewMatrix();
        shader_program.setUniform(view_mat_location, view);
        
        terrain.draw(shader_program);
        
        shader_program.setUniform(light_position_world_location, world_light_position);
        shader_program.setUniform(light_position_gem1_location, gem1_position);
        shader_program.setUniform(light_position_gem2_location, gem2_position);

        double oscillation = fabs(sinf(window.getTime()));
        
        glm::mat3 light_properties_gem = glm::mat3(1.0, 1.0, 1.0,
                                                   3.0f + (5.0f * oscillation), 0.0, 0.0,
                                                   0.0, 0.0, 0.0);
        
        shader_program.setUniform(light_properties_world_location, light_properties_world);
        shader_program.setUniform(light_properties_gem_location, light_properties_gem);

        gem1.draw(shader_program);
        gem2.draw(shader_program);

        for (int i = 0; i < NUM_POINTS; i++) {
            points[i]->draw(shader_program);
        }

        score_manager.updateScore(player.points());
        score_manager.drawText(&shader_program);
        collision_manager.checkCollisions(2.0f);

        window.pollEvents();
        window.swapBuffers();
        
        while(window.getTime() < last_tick+1/FPS);
        last_tick = window.getTime();
    }

    glfwTerminate();
    
    return 0;
}
