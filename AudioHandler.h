#include <iostream>
#include <cmath>
#include <vector>
#include <portaudio.h>
#include "MP3Player.h"

struct AudioDevice {
	int id;
	std::string name;
	int maxInputChannels;
	int maxOutputChannels;
};

class AudioHandler {
public:
	AudioHandler();
	~AudioHandler();

	bool openStream(int inputDeviceId, int outputDeviceId, MP3Player* player);
	void start();
	void stop();
	std::vector<AudioDevice> listDevices() const;

private:
	int inChannels;
	int outChannels;
	float smoothedGain = 1.0f;
	PaStream* stream;
	MP3Player* mp3Player;
	static int audioCallback(const void* inputBuffer, void* outputBuffer,
                                 unsigned long framesPerBuffer,
                                 const PaStreamCallbackTimeInfo* timeInfo,
                                 PaStreamCallbackFlags statusFlags,
                                 void* userData);
};

