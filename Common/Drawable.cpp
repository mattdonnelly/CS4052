//
//  Drawable.cpp
//  Assignment 5
//
//  Created by Matt Donnelly on 06/12/2014.
//  Copyright (c) 2014 Matt Donnelly. All rights reserved.
//

#include "Drawable.h"

Drawable::Drawable(double x, double y, double z) : Drawable(glm::vec3(x, y, z)) { }

Drawable::Drawable(glm::vec3 loc) {
    location = loc;
    vao = NULL;
    texture = NULL;
    scale = glm::vec3(1.0f, 1.0f, 1.0f);
}

void Drawable::draw(GLProgram shader_program) {
    vao->bind();
    
    texture->bindTexture(GL_TEXTURE0);
    shader_program.setUniform("tex", 0);
    
    glm::mat4 model = glm::translate(glm::mat4(1.0f), location);
    model = glm::scale(model, scale);
    shader_program.setUniform("model", model);

    vao->draw();
}

GLVertexArray * Drawable::loadVertexArray(const char *file_name) {
    int point_count = 0;
    GLfloat *vp, *vt, *vn;
    assert(load_obj_file(file_name, vp, vt, vn, point_count));
    
    GLBuffer points_vbo = GLBuffer::GLBuffer(vp, 3, sizeof(float) * 3 * point_count);
    GLBuffer tex_vbo = GLBuffer::GLBuffer(vt, 2, sizeof(float) * 2 * point_count);
    GLBuffer normals_vbo = GLBuffer(vn, 3, sizeof(float) * 3 * point_count);
    
    delete vp; delete vt; delete vn;
    
    std::vector<GLBuffer> buffers;
    buffers.emplace_back(points_vbo);
    buffers.emplace_back(tex_vbo);
    buffers.emplace_back(normals_vbo);
    
    return new GLVertexArray(buffers, point_count);
}
