#include <iostream>
#include "AudioHandler.h"

#define FRAMES_PER_BUFFER 1024
#define THRESHOLD 0.05f
#define MINGAIN 0.0f
#define MAXGAIN 2.0f

AudioHandler::AudioHandler() : stream(nullptr){	
	PaError err = Pa_Initialize();
	if(err != paNoError){
		throw std::runtime_error("Failed to initialize PortAudio: " + std::string(Pa_GetErrorText(err)));
	}
}

AudioHandler::~AudioHandler(){
	if(stream){
		Pa_StopStream(stream);
		Pa_CloseStream(stream);
	}
	Pa_Terminate;
}

std::vector<AudioDevice> AudioHandler::listDevices() const{
	std::vector<AudioDevice> devices;
	int numDevices = Pa_GetDeviceCount();
	if(numDevices < 0){
		throw std::runtime_error("Pa_GetDeviceCount error");
	}

	for(int i = 0; i < numDevices; i++){
		const PaDeviceInfo* info = Pa_GetDeviceInfo(i);
		AudioDevice device;
		device.id = i;
		device.name = info->name;
		device.maxInputChannels = info->maxInputChannels;
		device.maxOutputChannels = info->maxOutputChannels;
		devices.push_back(device);
	}
	return devices;
}

bool AudioHandler::openStream(int inputDeviceId, int outputDeviceId, MP3Player* player) {
	//load MP3 Player
	if(!player || !player->isLoaded()){
		std::cerr << "Invalid or unloaded MP3Player\n";
		return false;
	}
	mp3Player = player;

	//Set up Input/Output streams
	PaStreamParameters inputParams, outputParams;
        const PaDeviceInfo* inputInfo = Pa_GetDeviceInfo(inputDeviceId);
	const PaDeviceInfo* outputInfo = Pa_GetDeviceInfo(outputDeviceId);

	if(!inputInfo || !outputInfo) 
		return false;

	inChannels = std::min(2, inputInfo->maxInputChannels);
	outChannels = std::min(2, outputInfo->maxOutputChannels);
	if (inChannels == 0 || outChannels == 0) {
		std::cerr << "Invalid channel count (in=" << inChannels << ", out=" << outChannels << ")\n";
	        return false;
    	}

	int sampleRate = player->getSampleRate();

	inputParams.device = inputDeviceId;
        inputParams.channelCount = inChannels;
        inputParams.sampleFormat = paFloat32;
        inputParams.suggestedLatency = inputInfo->defaultLowInputLatency;
        inputParams.hostApiSpecificStreamInfo = nullptr;

        outputParams.device = outputDeviceId;
        outputParams.channelCount = outChannels;
        outputParams.sampleFormat = paFloat32;
	outputParams.suggestedLatency = outputInfo->defaultLowOutputLatency;
        outputParams.hostApiSpecificStreamInfo = nullptr;

        PaError err = Pa_OpenStream(&stream, &inputParams, &outputParams, sampleRate, FRAMES_PER_BUFFER, paClipOff, AudioHandler::audioCallback, this);

	if(err != paNoError){
		std::cerr << "Error Opening Stream: " << Pa_GetErrorText(err) << "\n";
		return false;
	}

	std::cout << "Opened stream with "<< inChannels << " input channels, " << outChannels << " output channels\n";

	return true;
}

void AudioHandler::start(){
	if(stream){
		Pa_StartStream(stream);
	}
}

void AudioHandler::stop(){
	if(stream){
		Pa_StopStream(stream);
	}
}

int AudioHandler::audioCallback(const void* inputBuffer, void* outputBuffer, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void* userData) {
        AudioHandler* self = static_cast<AudioHandler*>(userData);
	const float* in = (const float*)inputBuffer;
        float* out = (float*)outputBuffer;
	
	//get peak volume of mic
	float peak = 0.0f;
	for(unsigned long i =0; i < framesPerBuffer * self->inChannels; ++i){
		float absVal = std::fabs(in[i]);
		if(absVal > peak) peak = absVal;
	}
	//Get volume of frame
	float gain = MINGAIN + (MAXGAIN - MINGAIN) * peak;
	gain = (gain < MINGAIN) ? MINGAIN : (gain > MAXGAIN) ? MAXGAIN : gain;

	//output nothing if silent
	std::fill(out, out + framesPerBuffer * self->outChannels, 0.0f);

	//fill output when input exist
	if (inputBuffer && self->mp3Player){


		//only write if volume is above threshold
		if(peak < THRESHOLD){
			std::fill(out, out + framesPerBuffer * self->outChannels, 0.0f);
			return paContinue;
		}

		size_t totalFramesWritten = 0;


		while(totalFramesWritten < framesPerBuffer){
			size_t framesRead = self->mp3Player->readFrames(out + totalFramesWritten * self->outChannels, framesPerBuffer - totalFramesWritten);

			//EOF (Mp3)
			if(framesRead == 0){
				//Loop file
				self->mp3Player->rewind();
				//std::cerr << "[Callback] MP3 reached EOR - rewinding.\n";
				continue;
			}

			totalFramesWritten += framesRead;
		}
		//Apply volume
		self->smoothedGain = 0.8 * self->smoothedGain + 0.2f * gain;
		for(unsigned long i = 0; i < framesPerBuffer * self->outChannels; ++i){
			out[i] *= self->smoothedGain;
		}
	}
        return paContinue;
}
