#pragma once
#include <string>

namespace RulesBasedAlertingSystem
{
	struct Alerts
	{
		std::string deviceId;
		double value;
		std::string message;
	};
}
