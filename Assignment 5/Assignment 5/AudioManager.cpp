//
//  AudioManager.cpp
//  Assignment 5
//
//  Created by Matt Donnelly on 07/12/2014.
//  Copyright (c) 2014 Matt Donnelly. All rights reserved.
//

#include "AudioManager.h"
#include <iostream>

AudioManager::AudioManager() {
    audio_engine = irrklang::createIrrKlangDevice();
    if (!audio_engine) {
        throw std::runtime_error("Error initialising audio engine");
    }
}

AudioManager::~AudioManager() {
    audio_engine->drop();
}

AudioManager* AudioManager::sharedManager() {
    static AudioManager *_sharedManager = new AudioManager();
    return _sharedManager;
}

void AudioManager::playMusic() {
    audio_engine->play2D("/Users/mattdonnelly/Documents/College/Computer Graphics/Assignment 5/audio/music.mp3", true);
}

void AudioManager::playItemPickUp() {
    irrklang::ISound *sound = audio_engine->play2D("/Users/mattdonnelly/Documents/College/Computer Graphics/Assignment 5/audio/point.mp3", false, true);
    sound->setVolume(0.4);
    sound->setIsPaused(false);
}

irrklang::ISound *AudioManager::playHealthUp() {
    irrklang::ISound *sound = audio_engine->play2D("/Users/mattdonnelly/Documents/College/Computer Graphics/Assignment 5/audio/health.mp3", true, true);
    sound->setVolume(0.4);
    return sound;
}

void AudioManager::playGameOver() {
    audio_engine->play2D("/Users/mattdonnelly/Documents/College/Computer Graphics/Assignment 5/audio/dead.mp3", false);
}
