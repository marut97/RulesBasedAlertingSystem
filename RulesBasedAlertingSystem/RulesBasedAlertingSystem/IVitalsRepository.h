#pragma once
#include "AlertingUnit.h"
#include "Alerts.h"
#include "Device.h"
#include "Patient.h"
#include "PatientVitals.h"
#include <string.h>
namespace RulesBasedAlertingSystem {
	class IVitalsRepository
	{
	public: virtual ~IVitalsRepository() {}
	public: virtual bool WriteVitals(Device device);
	public: virtual std::vector<std::string> ReadVitals(std::string patientID);
	};
}