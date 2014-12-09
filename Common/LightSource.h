//
//  LightSource.h
//  Assignment 5
//
//  Created by Matt Donnelly on 09/12/2014.
//  Copyright (c) 2014 Matt Donnelly. All rights reserved.
//

#pragma once

#include <glm/glm.hpp>
#include "GLProgram.h"

class LightSource {
public:
    LightSource(glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float attenuation, float shininess = 100.0f);
    
    glm::vec3 position;
    
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;

    float attenuation;
    float shininess;
    
    void render_light_source(GLProgram *shader_program);
    
private:
    int _index;
    static int _count;
    
    const GLchar *getUniformName(const char *name);

    const GLchar *_position_name;
    const GLchar *_ambient_name;
    const GLchar *_diffuse_name;
    const GLchar *_specular_name;
    const GLchar *_attenuation_name;
    const GLchar *_shininess_name;
};
