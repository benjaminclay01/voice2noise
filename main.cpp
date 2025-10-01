#include "AudioHandler.h"
#include <iostream>

int main() {
	try {
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
	
	        if (audio.openStream(inputId, outputId)) {
	            audio.start();
	            std::cout << "Passthrough running. Press Enter to quit...\n";
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

