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
    void setThreshold(int multiplier);
	void start();
	void stop();
	std::vector<AudioDevice> listDevices() const;

private:
	int inChannels;
	int outChannels;
    float threshold = 0.05f;
	float smoothedGain = 1.0f;
    PaStream* stream = nullptr;
    MP3Player* mp3Player = nullptr;
    static int audioCallback(const void* inputBuffer, void* outputBuffer,
                                 unsigned long framesPerBuffer,
                                 const PaStreamCallbackTimeInfo* timeInfo,
                                 PaStreamCallbackFlags statusFlags,
                                 void* userData);
};

