#define DR_MP3_IMPLEMENTATION
#include "dr_mp3.h"

#include "MP3Player.h"
#include <iostream>

MP3Player::MP3Player(const std::string& filename) : loaded(false){
	//ensure it inits properly
	if(!drmp3_init_file(&mp3, filename.c_str(), nullptr)){
		std::cerr << "Failed to open MP3: " << filename << "\n";
		return;
	}
	loaded = true;
	std::cout << "Loaded MP3: " << filename << " (" << mp3.channels << "ch, " << mp3.sampleRate << "Hz)\n";
}

MP3Player::~MP3Player(){
	if (loaded) drmp3_uninit(&mp3);
}

bool MP3Player::isLoaded() const {
	return loaded;
}

size_t MP3Player::readFrames(float* buffer, size_t framesToRead){
    if(!this->loaded){
		return 0;
    }
	return drmp3_read_pcm_frames_f32(&mp3, framesToRead, buffer);
}

void MP3Player::rewind(){
	if(loaded){
		drmp3_seek_to_pcm_frame(&mp3, 0);
	}
}


int MP3Player::getSampleRate() const {
	return loaded ? (int)mp3.sampleRate : 0;
}

int MP3Player::getChannels() const {
	return loaded ? (int)mp3.channels : 0;
}
