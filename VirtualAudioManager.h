#pragma once
#include <string>

class VirtualAudioManager {
public:
	VirtualAudioManager(const std::string& sinkName = "NoiseSink");
	~VirtualAudioManager();

	bool setup();
	void cleanup();

	bool sinkExists() const;
	std::string getSinkName() const {return sinkName;}

private:
	std::string sinkName;
	int sinkModuleId;
	int loopbackModuleId;

	std::string runCommand(const std::string& cmd) const;
};
