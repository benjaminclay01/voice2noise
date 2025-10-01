#include <iostream>
#include "AudioHandler.h"

#define SAMPLE_RATE 44100
#define FRAMES_PER_BUFFER 512

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


bool AudioHandler::openStream(int inputDeviceId, int outputDeviceId) {
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

	int sampleRate = inputInfo->defaultSampleRate;

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
	
	//output nothing if silent
        if (!inputBuffer) {
            for (unsigned long i = 0; i < framesPerBuffer * self->outChannels; i++) {
                out[i] = 0.0f;
            }
	//otherwise, just pass to output
	} else {
                for (unsigned long i = 0; i < framesPerBuffer; i++) {
			if(self->inChannels == 1 && self->outChannels == 2){
				//duplicate mono to stereo outputs
				float sample = *in++;
				*out++ = sample;
				*out++ = sample;
			}else{ //otherwise just copy what fits and drop the rest
				for(int ch = 0; ch < self->outChannels; ch++){
					if(ch < self->inChannels){
						*out++ = *in++;
					}else{
						*out++ = 0.0f;
					}
				}
			}
		}
        }
        return paContinue;
}
