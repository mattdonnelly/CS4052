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
    LightSource(glm::vec3 position, glm::vec4 ambient, glm::vec4 diffuse, glm::vec4 specular);
    
    glm::vec3 position;
    
    glm::vec4 ambient;
    glm::vec4 diffuse;
    glm::vec4 specular;
    
    void render_light_source(GLProgram *shader_program);
    
private:
    int _index;
    static int _count;
    
    const GLchar *getUniformName(const char *name);
    
    const GLchar *_position_name;
    
    const GLchar *_ambient_name;
    const GLchar *_diffuse_name;
    const GLchar *_specular_name;
};
