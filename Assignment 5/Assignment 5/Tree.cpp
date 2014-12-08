//
//  Tree.cpp
//  Assignment 5
//
//  Created by Matt Donnelly on 08/12/2014.
//  Copyright (c) 2014 Matt Donnelly. All rights reserved.
//

#include "Tree.h"
#include <random>

Tree::Tree(glm::vec3 location) : Drawable(location) {
    vao = new GLVertexArray::GLVertexArray("/Users/mattdonnelly/Documents/College/Computer Graphics/Assignment 5/obj/tree1.obj");
    texture = new GLTexture::GLTexture("/Users/mattdonnelly/Documents/College/Computer Graphics/Assignment 5/tex/tree1.png");
}

std::vector<Tree *> Tree::generateRandomTrees(const int count, int min, int max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<int> dis(min, max);
    
    std::vector<Tree *> trees;
    for (int i = 0; i < count; i++) {
        double x = dis(gen);
        double y = 0.0;
        double z = dis(gen);
        Tree *t = new Tree(glm::vec3(x, y, z));
        trees.push_back(t);
    }
    
    return trees;
}

bool Tree::locationWillCollide(glm::vec3 obj_loc) const {
    return glm::distance(location, obj_loc) < 7.0f;
}
