//
//  main.cpp
//  Assignment 5
//
//  Created by Matt Donnelly on 09/11/2014.
//  Copyright (c) 2014 Matt Donnelly. All rights reserved.
//

#define GLM_FORCE_RADIANS

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <math.h>
#include <irrKlang.h>

#include "Player.h"
#include "GLShader.h"
#include "GLProgram.h"
#include "Window.h"

#include "Terrain.h"
#include "Gem.h"
#include "Point.h"

#define NUM_POINTS 15

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

int main(int argc, const char * argv[]) {
    Window window = Window("Assignment 5", 1280, 720);
    
    GLProgram shader_program = GLProgram("/Users/mattdonnelly/Documents/College/Computer Graphics/Assignment 5/Assignment 5/vertex_shader.glsl", "/Users/mattdonnelly/Documents/College/Computer Graphics/Assignment 5/Assignment 5/fragment_shader.glsl");
    
    Terrain terrain = Terrain();
    
    const glm::vec3 world_light_position = glm::vec3(0, 15.0f, 0.0f);
    const glm::vec3 gem1_position = glm::vec3( 70.0f, 4.0f,  70.f);
    const glm::vec3 gem2_position = glm::vec3(-70.0f, 4.0f, -70.f);
    
    Gem gem1 = Gem(gem1_position);
    Gem gem2 = Gem(gem2_position);
    
    std::vector<Point> points = Point::generateRandomPoints(NUM_POINTS);
    
    glm::mat4 projection = glm::perspective(45.0f, window.aspectRatio(), 0.1f, 1000.0f);
    
    Player player = Player();
    player.position = glm::vec3(0.0f, 5.0f, 0.0f);
    player.forward_direction = glm::vec3(-1.0f, 0.0f, 0.0f);
    player.speed = 15.0f;
    window.player = &player;

    shader_program.use();
    
    const int proj_mat_location = shader_program.uniform("projection");
    const int view_mat_location = shader_program.uniform("view");
    
    const int light_position_world_location = shader_program.uniform("light_position_world");
    const int light_position_gem1_location = shader_program.uniform("light_position_gem1");
    const int light_position_gem2_location = shader_program.uniform("light_position_gem2");

    const int light_properties_world_location = shader_program.uniform("light_properties_world");
    const int light_properties_gem_location = shader_program.uniform("light_properties_gem");
    
    glm::mat3 light_properties_world = glm::mat3(0.7, 0.9, 0.9,
                                                 0.5, 0.7, 0.5,
                                                 0.1, 0.2, 0.2);    
    
    irrklang::ISoundEngine *audio_engine = irrklang::createIrrKlangDevice();
    
    if (!audio_engine) {
        std::cout << "Error initialising audio engine" << std::endl;
        return 0;
    }
    
    audio_engine->play2D("/Users/mattdonnelly/Documents/College/Computer Graphics/Assignment 5/audio/music.mp3", true);

    while (!window.shouldClose()) {
        shader_program.use();

        glm::mat4 view = player.getViewMatrix();
        
        shader_program.setUniform(proj_mat_location, projection);
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
        
        gem1.scale = glm::vec3(oscillation, oscillation, oscillation);
        gem1.draw(shader_program);
        
        gem2.scale = gem1.scale;
        gem2.draw(shader_program);

        for (int i = 0; i < NUM_POINTS; i++) {
            Point p = points[i];
            p.draw(shader_program);
        }

        window.pollEvents();
        window.presentBuffer();
    }

    audio_engine->drop();
    glfwTerminate();
    
    return 0;
}
