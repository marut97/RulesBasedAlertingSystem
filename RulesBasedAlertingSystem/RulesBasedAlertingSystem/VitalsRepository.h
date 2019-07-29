#pragma once
#include "IVitalsRepository.h"

namespace RulesBasedAlertingSystem 
{
	class VitalsRepository : public IVitalsRepository
	{
	public:
		bool writeVitals(PatientVitals vitals) override;
		std::vector<PatientVitals> readVitals(std::string patientID) override;
		VitalsRepository();
	private:
		std::string vitalsToString(PatientVitals vitals);
		PatientVitals stringToVitals(std::string line);
	private:
		std::string m_vitalsRepositoryPath;
	};
}