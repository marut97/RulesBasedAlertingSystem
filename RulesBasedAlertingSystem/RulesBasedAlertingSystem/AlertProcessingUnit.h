#pragma once
#include "SharedQueue.h"
#include "IPatientRepository.h"
#include "IVitalsRepository.h"
#include "AlertingUnit.h"

namespace RulesBasedAlertingSystem
{
	class AlertProcessingUnit
	{
	public:
		AlertProcessingUnit(IPatientRepository &patientRepo, IVitalsRepository &vitalsRepo);
		void initialize();
	private:
		void process(AlertingUnit &alertingUnit);

	private:
		SharedQueue m_queue;
		IPatientRepository &m_patientRepository;
		IVitalsRepository &m_vitalsRepository;
	};
}