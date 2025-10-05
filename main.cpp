#include "AudioHandler.h"
#include "MP3Player.h"
#include <iostream>

int main(int argc, char** argv) {
	//ensure proper arguments are passed
	if(argc < 2){
		std::cout << "Usage: " << argv[0] << " <mp3File>\n";
		return 1;
	}

	try {
		//set up MP3 file
		std::string mp3File = "voices/";
		mp3File.append(argv[1]);
		MP3Player player(mp3File);
		if(!player.isLoaded()){
			std::cerr << "Error initializing mp3 file!\n";
			return 1;
		}

		//get device IDs
		AudioHandler audio;

		auto device_list = audio.listDevices();
                std::cout << "Available devices:\n";
                for (const auto& d : device_list) {
                    std::cout << d.id << ": " << d.name
        	              << " (inputs: " << d.maxInputChannels
                	      << ", outputs: " << d.maxOutputChannels << ")\n";
	        }

        	int inputId, outputId;
	        std::cout << "Enter input device ID: ";
	        std::cin >> inputId;
	        std::cout << "Enter output device ID: ";
	        std::cin >> outputId;
	
		//open Audio Stream
	        if (audio.openStream(inputId, outputId, &player)) {
	            audio.start();
	            std::cout << "Passthrough running with file " << argv[1] <<  ". Press Enter to quit...\n";
	            std::cin.ignore(); // consume newline
	            std::cin.get();
	            audio.stop();
	        } else {
	            std::cerr << "Failed to open stream.\n";
	        }
        } catch (std::exception& e) {
	        std::cerr << "Fatal error: " << e.what() << "\n";
        }
}

