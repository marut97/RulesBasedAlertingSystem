#pragma once
#include "PatientVitals.h"

namespace RulesBasedAlertingSystem {
	class IVitalsRepository
	{
	public: 
		virtual ~IVitalsRepository() {}
		virtual bool writeVitals(PatientVitals vitals) = 0;
		virtual std::vector<std::string> readVitals(std::string patientID) = 0;
	};
}