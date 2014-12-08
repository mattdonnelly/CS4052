//
//  AudioManager.h
//  Assignment 5
//
//  Created by Matt Donnelly on 07/12/2014.
//  Copyright (c) 2014 Matt Donnelly. All rights reserved.
//

#pragma once

#include <irrKlang.h>

class AudioManager {
public:
    static AudioManager *sharedManager();
    
    AudioManager();
    ~AudioManager();
    
    void playMusic();
    void playItemPickUp();
    irrklang::ISound *playHealthUp();
    void playWon();
    void playGameOver();

private:
    irrklang::ISoundEngine *audio_engine;
};
