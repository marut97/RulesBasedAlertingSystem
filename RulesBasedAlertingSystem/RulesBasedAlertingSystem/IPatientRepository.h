#pragma once
#include "Device.h"
#include "Patient.h"
#include "PatientVitals.h"

namespace RulesBasedAlertingSystem {
	class IPatientRepository
	{
	public: virtual ~IPatientRepository() {}
	public: virtual bool Register(Patient patient);
	public: virtual bool Update(Patient patient);
	public: virtual Device Read(std::string patientID);
	public: virtual std::vector<Patient> ReadAll();
	};
}