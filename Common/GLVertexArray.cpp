//
//  GLVertexArray.cpp
//  Assignment 4
//
//  Created by Matt Donnelly on 16/11/2014.
//  Copyright (c) 2014 Matt Donnelly. All rights reserved.
//

#include "GLVertexArray.h"
#include <IL/il.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <iostream>

GLVertexArray::GLVertexArray(const char *filename) {
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(filename, aiProcess_Triangulate);
    if(!scene){
        fprintf(stderr, "%s", importer.GetErrorString());
    }
    std::vector<const aiMesh *> meshes(scene->mMeshes,scene->mMeshes+scene->mNumMeshes);
    aiMesh *mesh = scene->mMeshes[0];
    
    GLuint buffer;
    
    glGenVertexArrays(1, &_object);
    glBindVertexArray(_object);
    
    _point_count = mesh->mNumFaces * 3;
    
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 *_point_count, mesh->mVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0 , 3, GL_FLOAT, 0, 0, 0);
    
    float *tex_coords = new float[_point_count * 2];
    
    for(int i = 0; i < meshes[0]->mNumVertices; i++) {
        tex_coords[i * 2]   = mesh->mTextureCoords[0][i].x;
        tex_coords[i * 2 + 1] = mesh->mTextureCoords[0][i].y;
    }
    
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 2 * _point_count, tex_coords, GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, 0, 0, 0);
    
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * _point_count, mesh->mNormals, GL_STATIC_DRAW);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, 0, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void GLVertexArray::draw() const {
    glBindVertexArray(_object);
    glDrawArrays(GL_TRIANGLES, 0, _point_count);
    glBindVertexArray(0);
}

GLint GLVertexArray::point_count() const {
    return _point_count;
}
