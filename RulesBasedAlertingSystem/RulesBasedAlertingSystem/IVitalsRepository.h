#pragma once
#include "Device.h"
#include "PatientVitals.h"

namespace RulesBasedAlertingSystem {
	class IVitalsRepository
	{
	public: virtual ~IVitalsRepository() {}
	public: virtual bool WriteVitals(Device device);
	public: virtual std::vector<std::string> ReadVitals(std::string patientID);
	};
}