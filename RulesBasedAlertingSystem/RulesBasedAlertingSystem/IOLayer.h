#pragma once
#include <string>
#include <vector>

namespace RulesBasedAlertingSystem
{
	class IOLayer
	{
	public:
		static std::string readInput(std::string menu);
		static std::string readMessage(std::string menu);
		static std::string readDevices(std::string menu, int deviceSize);
		static std::string readVitals();
		static void display(std::string output);
		static void criticalAlert(std::string input);
		static void warningAlert(std::string input);
		static void clearScreen();
	};
}
