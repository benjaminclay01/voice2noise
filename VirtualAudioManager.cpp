#include "VirtualAudioManager.h"
#include <cstdlib>
#include <iostream>
#include <array>
#include <memory>

VirtualAudioManager::VirtualAudioManager(const std::string& name): sinkName(name), sinkModuleId(-1), loopbackModuleId(-1){}

VirtualAudioManager::~VirtualAudioManager() {cleanup();}

std::string VirtualAudioManager::runCommand(const std::string& cmd) const{
	std::array<char, 256> buffer{};
	std::string result;
	std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd.c_str(), "r"), pclose);
	if(!pipe) 
		return "";
	while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
		result += buffer.data();
	return result;
}

bool VirtualAudioManager::sinkExists() const {
	std::string sinks = runCommand("pactl list short sinks");
	return sinks.find(sinkName) != std::string::npos;
}

bool VirtualAudioManager::setup(){
	//check for existing sink
	std::cout<< "[Audio Setup] Checking for existing virtual sink...\n";

	if(sinkExists()){
		std::cout << "[AudioSetup] Found existing sink: " << sinkName << "\n";
		return true;
	}
	
	//if doesn't exist, create sink
	std::string createSinkCmd = "pactl load-module module-null-sink sink_name=" + sinkName + " sink_properties=device.description=" + sinkName;
	std::string sinkId = runCommand(createSinkCmd);
	if(sinkId.empty()){
		std::cerr << "[Audio Setup] Failed to create virtual sink!\n";
		return false;
	}
	sinkModuleId = std::stoi(sinkId);
	std::cout << "[Audio Setup] Created Sink '" << sinkName << "' (module ID " << sinkModuleId << ")\n";

	//and create loopback for capture
	std::string loopbackCmd = "pactl load-module module-loopback source=" + sinkName + ".monitor";
	std::string loopbackId = runCommand(loopbackCmd);
	if(loopbackId.empty()){
		std::cerr << "[Audio Setup] Failed to create loopback!\n";
		return false;
	}
	loopbackModuleId = std::stoi(loopbackId);
	std::cout << "[Audio Setup] Created loopback (module ID " << loopbackModuleId << ")\n";

	return true;
}

void VirtualAudioManager::cleanup(){
	if(loopbackModuleId != -1){
		std::string unloadLoopback = "pactl unload-module " + std::to_string(loopbackModuleId);
		std::system(unloadLoopback.c_str());
		std::cout << "[Audio Cleanup] Unloaded loopback module " << loopbackModuleId << "\n";
		loopbackModuleId = -1;
	}
	if (sinkModuleId != -1) {
        	std::string unloadSink = "pactl unload-module " + std::to_string(sinkModuleId);
	        std::system(unloadSink.c_str());
	        std::cout << "[Audio Cleanup] Unloaded virtual sink module " << sinkModuleId << "\n";
	        sinkModuleId = -1;
    }
}
