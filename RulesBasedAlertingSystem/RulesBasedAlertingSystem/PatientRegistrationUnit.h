#include "Patient.h"
#include "IPatientRepository.h"
#include "DeviceRepository.h"
#include "DeviceRegistrationUnit.h"


namespace RulesBasedAlertingSystem
{

	class PatientRegistrationUnit
	{
	public:
		PatientRegistrationUnit(IPatientRepository &patientRepo, IDeviceRepository &deviceRepo);
		void readInput();
	private:
		void generateDeviceList();
		void updateRegisteredPatients();
		void readAllRegisteredPatients();
		void readRegisteredPatients();
		void deleteRegisteredPatient();
		void registerPatient();
		Device registerDevice(std::string deviceID);
		bool operationInPatientRegistration(int operation);
	private:
		IPatientRepository &m_patientRepo;
		IDeviceRepository &m_deviceRepo;
		std::map<std::string, Device> m_deviceList;

	};
}