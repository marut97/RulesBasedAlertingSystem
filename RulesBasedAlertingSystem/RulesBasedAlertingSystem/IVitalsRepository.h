#pragma once
#include "Device.h"
#include "PatientVitals.h"

namespace RulesBasedAlertingSystem {
	class IVitalsRepository
	{
	public: 
		virtual ~IVitalsRepository() {}
		virtual bool writeVitals(Device device) = 0;
		virtual std::vector<std::string> readVitals(std::string patientID) = 0;
	};
}