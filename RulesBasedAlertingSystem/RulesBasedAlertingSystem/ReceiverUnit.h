#pragma once
#include "PatientVitals.h"
#include "Patient.h"
#include "SharedQueue.h"
#include <map>

namespace RulesBasedAlertingSystem
{
	class ReceiverUnit
	{
	public:
		ReceiverUnit(SharedQueue &queue, std::map<std::string, Patient> &map);
		void inputProcess() const;
	private:
		bool unboxInput(const std::string &input, PatientVitals &vitals)const;
	private:
		SharedQueue &m_queue;
		std::map<std::string, Patient> &m_map;
	};
}