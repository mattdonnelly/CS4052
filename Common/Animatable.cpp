//
//  Animatable.cpp
//  Assignment 5
//
//  Created by Matt Donnelly on 07/12/2014.
//  Copyright (c) 2014 Matt Donnelly. All rights reserved.
//

#include "Animatable.h"
#include <GLFW/glfw3.h>

Animatable::Animatable() {
    previous_seconds = glfwGetTime();
}

double Animatable::delta() {
    double current_seconds = glfwGetTime();
    double elapsed_seconds = current_seconds - previous_seconds;
    previous_seconds = current_seconds;
    
    return elapsed_seconds;
}
