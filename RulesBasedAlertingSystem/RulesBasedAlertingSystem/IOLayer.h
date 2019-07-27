#pragma once
#include <string>

namespace RulesBasedAlertingSystem
{
	class IOLayer
	{
	public:
		static std::string readInput(std::string menu);
		static std::string readMessage(std::string menu);
		static std::string readVitals();
		static void criticalAlert(std::string input);
		static void warningAlert(std::string input);
	};
}
