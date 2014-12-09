//
//  LightSource.cpp
//  Assignment 5
//
//  Created by Matt Donnelly on 09/12/2014.
//  Copyright (c) 2014 Matt Donnelly. All rights reserved.
//

#include "LightSource.h"
#include <sstream>
#include <iostream>

int LightSource::_count = 0;

LightSource::LightSource(glm::vec3 p, glm::vec3 a, glm::vec3 d, glm::vec3 s, float att) {
    _index = _count;
    
    position = p;
    ambient = a;
    diffuse = d;
    specular = s;
    attenuation = att;

    _position_name = getUniformName("position");
    _ambient_name = getUniformName("ambient");
    _diffuse_name = getUniformName("diffuse");
    _specular_name = getUniformName("specular");
    _attenuation_name = getUniformName("attenuation");
    
    _count++;
}

const GLchar *LightSource::getUniformName(const char *name) {
    char *buffer = new char[50];
    sprintf(buffer, "light_sources[%d].%s", _index, name);
    return buffer;
}

void LightSource::render_light_source(GLProgram *shader_program) {
    shader_program->setUniform("num_lights", _count);
    shader_program->setUniform(_position_name, position);
    shader_program->setUniform(_ambient_name, ambient);
    shader_program->setUniform(_diffuse_name, diffuse);
    shader_program->setUniform(_specular_name, specular);
    shader_program->setUniform(_attenuation_name, attenuation);
}

