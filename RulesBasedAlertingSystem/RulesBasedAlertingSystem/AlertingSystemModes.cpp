#include "AlertingSystemModes.h"
#include "DeviceRegistrationUnit.h"
#include "PatientRegistrationUnit.h"
#include "AlertProcessingUnit.h"

#include<iostream>
#include<string>
#include "IOLayer.h"
#include "PatientRepository.h"
#include "VitalsRepository.h"
using namespace std;

namespace RulesBasedAlertingSystem {

	AlertingSystemModes::AlertingSystemModes()
	{
		m_deviceRepository.reset(new DeviceRepository());
		m_patientRepository.reset(new PatientRepository);
		m_vitalsRepository.reset(new VitalsRepository);
	}

	void AlertingSystemModes::displayModes()
	{

		
		string modeInput;
		do
		{
			modeInput =IOLayer::readInput("Select \n1.Device Registration   \n2.Patient Registration  \n3.Patient Monitor  \n4.Exit");
			try
			{
				selectMode(stoi(modeInput));
				system("CLS");
			}
			catch(...)
			{
				IOLayer::criticalAlert("Invalid input.  Try again... ");
			}
			
		} while (true);
	}


	void AlertingSystemModes::selectMode(int mode)
	{
		DeviceRegistrationUnit deviceRegistration(*m_deviceRepository);
		PatientRegistrationUnit patientRegistration(*m_patientRepository, *m_deviceRepository);
		AlertProcessingUnit alertProcessingUnit(*m_patientRepository, *m_vitalsRepository);

		switch (mode)
		{
		case 1:
			deviceRegistration.readInput();
			break; 
		case 2:
			patientRegistration.readInput();
			break;
		case 3:
			alertProcessingUnit.initialize();
			break;
		case 4:
			exit(0);
		default:
			IOLayer::criticalAlert("Invalid input.  Try again... ");
			break;
		}
	}


}
