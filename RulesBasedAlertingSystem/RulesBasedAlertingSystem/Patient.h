#pragma once
#include <string>
#include <map>
#include "Device.h"

namespace RulesBasedAlertingSystem {
	struct Patient
	{
		std::string patientId;
		std::map<std::string, Device> devices;
	};
}
