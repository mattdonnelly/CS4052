//
//  main.cpp
//  Assignment0
//
//  Created by Matt Donnelly on 23/09/2014.
//  Copyright (c) 2014 Matt Donnelly. All rights reserved.
//

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <stdio.h>
#include <assert.h>
#include <iostream>

void checkShaderStatus(GLuint shader) {
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    
    if (status == GL_FALSE) {
        GLint infoLogLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
        
        GLchar *strInfoLog = new GLchar[infoLogLength + 1];
        glGetShaderInfoLog(shader, infoLogLength, NULL, strInfoLog);
        
        fprintf(stderr, "Compilation error in shader: %s\n", strInfoLog);
        delete[] strInfoLog;
        
        glDeleteShader(shader);
    }
}

int main(int argc, const char *argv[]) {
    if (!glfwInit()) {
        fprintf (stderr, "ERROR: could not start GLFW3\n");
        return 1;
    }
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    GLFWwindow *window = glfwCreateWindow(640, 640, "Assignment 0", NULL, NULL);
    if (!window) {
        fprintf (stderr, "ERROR: could not open window with GLFW3\n");
        glfwTerminate();
        return 1;
    }
    
    glfwMakeContextCurrent(window);
    
    glewExperimental = GL_TRUE;
    glewInit();
    
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    
    float vertices[] = {
         0.0f,  0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
    };
    
    GLuint verticesBuffer = NULL;
    glGenBuffers(1, &verticesBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, verticesBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    GLuint vao = NULL;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    glBindBuffer(GL_ARRAY_BUFFER, verticesBuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    
    glEnableVertexAttribArray(0);
    
    const char *vertex_shader =
    "#version 400\n"
    "in vec3 vertex_position;"
    "uniform mat4 translation;"
    "uniform mat4 scale;"
    "uniform mat4 rotation;"
    "void main() {"
    "    gl_Position = translation * scale * rotation * vec4(vertex_position, 1.0);"
    "}";
    
    const char *fragment_shader =
    "#version 400\n"
    "out vec4 frag_colour;"
    "void main() {"
    "    frag_colour = vec4(1.0, 0.0, 0.0, 1.0);"
    "}";
    
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertex_shader, NULL);
    glCompileShader(vs);
    checkShaderStatus(vs);
    
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragment_shader, NULL);
    glCompileShader(fs);
    checkShaderStatus(fs);
    
    GLuint shader_programme = glCreateProgram ();
    glAttachShader(shader_programme, fs);
    glAttachShader(shader_programme, vs);
    
    glBindAttribLocation(shader_programme, 0, "vertex_position");
    
    glLinkProgram (shader_programme);
    
    int translation_loc = glGetUniformLocation (shader_programme, "translation");
    assert (translation_loc > -1);
    int rotation_loc = glGetUniformLocation (shader_programme, "rotation");
    assert (rotation_loc > -1);
    int scale_loc = glGetUniformLocation (shader_programme, "scale");
    assert (scale_loc > -1);
    
    float translation[] = {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };
    
    float rotation[] = {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };
    
    float scale[] = {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };
    
    float x_speed = 0.5f, y_speed = 0.5f, z_speed = 0.5f,
          scale_speed = 0.5f,
          x_rotation = 1.0f, y_rotation = 1.0f, z_rotation = 1.0f;
    
    while (!glfwWindowShouldClose (window)) {
        static double previous_seconds = glfwGetTime();
        double current_seconds = glfwGetTime();
        double elapsed_seconds = current_seconds - previous_seconds;
        previous_seconds = current_seconds;
        
        if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_Q)) {
            if (fabs(translation[12]) > 1.0f) {
                x_speed = -x_speed;
            }
            
            translation[12] += elapsed_seconds * x_speed;
        }
        if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_W)) {
            if (fabs(translation[13]) > 1.0f) {
                y_speed = -y_speed;
            }
            
            translation[13] += elapsed_seconds * y_speed;
        }
        if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_E)) {
            if (fabs(translation[14]) > 1.0f) {
                z_speed = -z_speed;
            }
            
            translation[14] += elapsed_seconds * z_speed;
        }
        if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_A)) {
            if (fabs(scale[0]) > 2.0f || scale[0] <= 0.0f) {
                scale_speed = -scale_speed;
            }
            
            scale[0]  += elapsed_seconds * scale_speed;
            scale[5]  += elapsed_seconds * scale_speed;
            scale[10] += elapsed_seconds * scale_speed;
        }
        if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_Z)) {
            float last_rot_x_angle = acos(rotation[5]);
    
            if (last_rot_x_angle >= 3.12) {
                x_rotation = -1.0f;
            }
            else if (last_rot_x_angle <= 0) {
                x_rotation = 1.0f;
            }
            
            rotation[5]  =  cos(elapsed_seconds * x_rotation + last_rot_x_angle);
            rotation[7]  =  sin(elapsed_seconds * x_rotation + last_rot_x_angle);
            rotation[9]  = -sin(elapsed_seconds * x_rotation + last_rot_x_angle);
            rotation[10] =  cos(elapsed_seconds * x_rotation + last_rot_x_angle);
        }
        if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_X)) {
            float last_rot_y_angle = acos(rotation[0]);
            
            if (last_rot_y_angle >= 3.12) {
                y_rotation = -1.0f;
            }
            else if (last_rot_y_angle <= 0) {
                y_rotation = 1.0f;
            }
            
            rotation[0]  =  cos(elapsed_seconds * y_rotation + last_rot_y_angle);
            rotation[8]  =  sin(elapsed_seconds * y_rotation + last_rot_y_angle);
            rotation[3]  = -sin(elapsed_seconds * y_rotation + last_rot_y_angle);
            rotation[10] =  cos(elapsed_seconds * y_rotation + last_rot_y_angle);
        }
        if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_C)) {
            float last_rot_z_angle = acos(rotation[5]);
            
            if (last_rot_z_angle >= 3.12) {
                z_rotation = -1.0f;
            }
            else if (last_rot_z_angle <= 0) {
                z_rotation = 1.0f;
            }
            
            rotation[0] =  cos(elapsed_seconds * z_rotation + last_rot_z_angle);
            rotation[1] =  sin(elapsed_seconds * z_rotation + last_rot_z_angle);
            rotation[4] = -sin(elapsed_seconds * z_rotation + last_rot_z_angle);
            rotation[5] =  cos(elapsed_seconds * z_rotation + last_rot_z_angle);
        }
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        glUseProgram(shader_programme);
        glBindVertexArray(vao);
        
        glUniformMatrix4fv(translation_loc, 1, false, translation);
        glUniformMatrix4fv(rotation_loc, 1, false, rotation);
        glUniformMatrix4fv(scale_loc, 1, false, scale);
        
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        glfwPollEvents();
        
        glfwSwapBuffers(window);
    }
    
    glfwTerminate();
    
    return 0;
}
