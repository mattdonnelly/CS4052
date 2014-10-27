#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <assert.h>
#include <string.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "teapot.h"

#define RETINA 1

#ifdef RETINA
    #define SCALE 2.0
#else
    #define SCALE 1.0
#endif

#define DEGREES_TO_RADIANS(angle) ((angle) / 180.0 * M_PI)

const int gl_width = 800;
const int gl_height = 800;

const int viewport_width  = gl_width / 2 * SCALE;
const int viewport_height = gl_height / 2 * SCALE;

std::string readShaderFile(std::string filename) {
    std::ifstream ifile(filename);
    std::string text;
    
    while( ifile.good() ) {
        std::string line;
        std::getline(ifile, line);
        text.append(line + "\n");
    }
    
    text += '\0';
    
    return text;
}

void printShaderStatus(GLuint shader) {
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    
    if (status == GL_FALSE) {
        GLint infoLogLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
        
        GLchar *strInfoLog = (char *)malloc(infoLogLength + 1);
        glGetShaderInfoLog(shader, infoLogLength, NULL, strInfoLog);
        
        fprintf(stderr, "Compilation error in shader: %s\n", strInfoLog);
        free(strInfoLog);
        
        glDeleteShader(shader);
    }
}

int main() {
    GLFWwindow *window = NULL;

    const GLubyte *renderer;
    const GLubyte *version;
    GLuint shader_programme;
    GLuint vao;
    
    if (!glfwInit()) {
        fprintf (stderr, "ERROR: could not start GLFW3\n");
        return 1;
    }
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    window = glfwCreateWindow(gl_width, gl_height, "Assignment 2", NULL, NULL);
    if (!window) {
        fprintf (stderr, "ERROR: opening OS window\n");
        return 1;
    }

    glfwMakeContextCurrent(window);
    
    glewExperimental = GL_TRUE;
    glewInit();
    
    renderer = glGetString(GL_RENDERER);
    version = glGetString(GL_VERSION);
    printf("Renderer: %s\n", renderer);
    printf("OpenGL version supported %s\n", version);

    {
        GLuint points_vbo, normals_vbo;
        glGenBuffers(1, &points_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof (teapot_vertex_points),
                     teapot_vertex_points, GL_STATIC_DRAW);
        
        glGenBuffers(1, &normals_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, normals_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof (teapot_normals),
                     teapot_normals, GL_STATIC_DRAW);
        
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, normals_vbo);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    }
    
    {
        std::string vertex_shader_str = readShaderFile("/Users/mattdonnelly/Documents/College/Computer Graphics/Assignment 2/Assignment 2/teapot.vert");
        GLchar const *vertex_shader_source = vertex_shader_str.c_str();

        std::string fragment_shader_str = readShaderFile("/Users/mattdonnelly/Documents/College/Computer Graphics/Assignment 2/Assignment 2/teapot.frag");
        GLchar const *fragment_shader_source = fragment_shader_str.c_str();

        GLuint vs, fs;
        vs = glCreateShader(GL_VERTEX_SHADER);
        fs = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(vs, 1, &vertex_shader_source, NULL);
        glShaderSource(fs, 1, &fragment_shader_source, NULL);
        
        glCompileShader(vs);
        printShaderStatus(vs);
        
        glCompileShader(fs);
        printShaderStatus(fs);
        
        shader_programme = glCreateProgram ();
        glAttachShader(shader_programme, fs);
        glAttachShader(shader_programme, vs);
        glLinkProgram (shader_programme);
    }

    int M_loc = glGetUniformLocation (shader_programme, "M");
    assert(M_loc > -1);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glClearColor(0.5, 0.5, 0.5, 1.0);
    
    float rotating_speed = 45.0f;
    float last_angle = 0.0f;
    
    while (!glfwWindowShouldClose (window)) {
        static double previous_seconds = glfwGetTime();
        double current_seconds = glfwGetTime();
        double elapsed_seconds = current_seconds - previous_seconds;
        previous_seconds = current_seconds;
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        glUseProgram(shader_programme);
        glBindVertexArray(vao);
        
        // TOP LEFT

        glm::mat4 projection = glm::ortho(-2.0f, 2.0f, 2.0f, -2.0f, 0.0f, 10.0f);
        glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 2.0f, 0.0001f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 model = glm::scale(glm::mat4(1.0f), glm::vec3(0.05f));
        glm::mat4 mvp = projection * view * model;
        glUniformMatrix4fv(M_loc, 1, GL_FALSE, glm::value_ptr(mvp));
        
        glViewport(0, viewport_height, viewport_width, viewport_height);
        glDrawArrays(GL_TRIANGLES, 0, teapot_vertex_count);
        
        // TOP RIGHT
        
        projection = glm::perspective(90.0f, 1.0f, 1.0f, 10.0f);
        view = glm::lookAt(glm::vec3(-2.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        mvp = projection * view * model;
        glUniformMatrix4fv(M_loc, 1, GL_FALSE, glm::value_ptr(mvp));
        
        glViewport(viewport_width, viewport_height, viewport_width, viewport_height);
        glDrawArrays(GL_TRIANGLES, 0, teapot_vertex_count);

        // BOTTOM LEFT
        
        if (last_angle > 359.0f) {
            last_angle = 0.0f;
        }
        
        last_angle += elapsed_seconds * rotating_speed;
        
        GLdouble xp = 2.0f * cos(DEGREES_TO_RADIANS(last_angle));
        GLdouble zp = 2.0f * sin(DEGREES_TO_RADIANS(last_angle));
        
        view = glm::lookAt(glm::vec3(xp, 0.0f, zp), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        mvp = projection * view * model;
        glUniformMatrix4fv(M_loc, 1, GL_FALSE, glm::value_ptr(mvp));
        
        glViewport(0, 0, viewport_width, viewport_height);
        glDrawArrays(GL_TRIANGLES, 0, teapot_vertex_count);
        
        // BOTTOM RIGHT
        
        projection = glm::perspective(45.0f, 1.0f, 1.0f, 10.0f);
        view = glm::lookAt(glm::vec3(2.5f, 2.5f, 2.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        mvp = projection * view * model;
        glUniformMatrix4fv(M_loc, 1, GL_FALSE, glm::value_ptr(mvp));
        
        glViewport(viewport_width, 0, viewport_width, viewport_height);
        glDrawArrays(GL_TRIANGLES, 0, teapot_vertex_count);
        
        glfwPollEvents();
        glfwSwapBuffers(window);
    }
    
    return 0;
}