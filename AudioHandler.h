#include <iostream>
#include <cmath>
#include <vector>
#include <portaudio.h>

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

	bool openStream(int inputDeviceId, int outputDeviceId);
	void start();
	void stop();
    std::vector<AudioDevice> listDevices() const;

private:
	int inChannels;
	int outChannels;
	PaStream* stream;
	static int audioCallback(const void* inputBuffer, void* outputBuffer,
                                 unsigned long framesPerBuffer,
                                 const PaStreamCallbackTimeInfo* timeInfo,
                                 PaStreamCallbackFlags statusFlags,
                                 void* userData);
};

