//
//  Animatable.h
//  Assignment 5
//
//  Created by Matt Donnelly on 07/12/2014.
//  Copyright (c) 2014 Matt Donnelly. All rights reserved.
//

#pragma once

class Animatable {
public:
    Animatable();
    
    double delta();

private:
    double previous_seconds;
};
