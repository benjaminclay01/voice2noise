#pragma once
#include "dr_mp3.h"
#include <string>
#include <vector>

class MP3Player{
public:
	explicit MP3Player(const std::string& filename);
    explicit MP3Player();
	~MP3Player();

	bool isLoaded() const;
	size_t readFrames(float* butter, size_t framesToRead);
	int getSampleRate() const;
	int getChannels() const;
	void rewind();
    void loadMP3(const std::string& filename);

private:
	drmp3 mp3;
	bool loaded;
};
