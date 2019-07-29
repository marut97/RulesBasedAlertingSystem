#include "AlertProcessingUnit.h"
#include "ReceiverUnit.h"


namespace RulesBasedAlertingSystem
{
	AlertProcessingUnit::AlertProcessingUnit(IPatientRepository &patientRepo, IVitalsRepository &vitalsRepo) : m_patientRepository(patientRepo) , m_vitalsRepository(vitalsRepo)
	{
	}

	void AlertProcessingUnit::initialize()
	{
		//Create map
		std::map<std::string, Patient> patientMap;
		auto patientsList = m_patientRepository.readAll();
		for (auto i = patientsList.begin(); i != patientsList.end(); i++)
			patientMap.insert({ i->patientId, *i });
		//Create a new thread for reciever unit
		ReceiverUnit receiver(m_queue, patientMap);
		std::thread inputThread(&ReceiverUnit::inputProcess, receiver);
		//Initialize Alert and create its object
		AlertingUnit alertingUnit(patientMap);
		//Call process
		process(alertingUnit);
		inputThread.join();
	}

	void AlertProcessingUnit::process(AlertingUnit &alertingUnit)
	{
		do
		{
			if (!m_queue.isEmpty())
			{
				PatientVitals vitalsInput = m_queue.dequeue();
				//Alerting System
				alertingUnit.checkLimits(vitalsInput);
				//Storage System
				m_vitalsRepository.writeVitals(vitalsInput);
			}
		} while (true);
	}

}