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
        bool try_again = false;
        double x, y, z;
        
        do {
            try_again = false;
            x = dis(gen);
            y = 0.0;
            z = dis(gen);

            for (int j = 0; j < trees.size(); j++) {
                Tree *t = trees[j];
                if (fabs(t->location.x - x) < 10.0 && fabs(t->location.z - z) < 10.0) {
                    try_again = true;
                    break;
                }
            }
            
        } while (try_again);

        Tree *t = new Tree(glm::vec3(x, y, z));
        trees.push_back(t);
    }
    
    return trees;
}

bool Tree::locationWillCollide(glm::vec3 obj_loc) const {
    return glm::distance(location, obj_loc) < 7.0f;
}
