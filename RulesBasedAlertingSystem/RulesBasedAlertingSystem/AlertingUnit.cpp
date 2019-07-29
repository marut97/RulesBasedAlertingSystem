#include "AlertingUnit.h"
#include "IOLayer.h"

namespace RulesBasedAlertingSystem
{
	AlertingUnit::AlertingUnit(std::map< std::string, Patient> &patientList) : m_patientList(patientList)
	{
		for (auto i = m_patientList.begin(); i != m_patientList.end(); i++)
		{
			m_criticalMap.insert({ i->first, std::vector<Alerts>() });
			m_warningMap.insert({ i->first, std::vector<Alerts>() });
		}
	}

	bool AlertingUnit::compare(double min, double max, double val)
	{
		if (val >= min && val < max)
			return true;
		return false;
	}

	void AlertingUnit::alertUser()
	{

		//Add clear screen here...
		IOLayer::clearScreen();
		IOLayer::criticalAlert("\tCritical");
		IOLayer::criticalAlert("************************");
		IOLayer::criticalAlert("************************");
		for (auto itr = m_criticalMap.begin(); itr != m_criticalMap.end(); itr++)
		{
			//Fix for displaying the vector
			if (itr->second.empty())
				continue;
			IOLayer::criticalAlert("Patient ID : " + itr->first + "\n");
			//do the same fix as above
			for each (Alerts var in itr->second)
			{
				IOLayer::criticalAlert(var.toString());
			}
			IOLayer::warningAlert("----------------------");
		}
		IOLayer::warningAlert("\tWarning");
		IOLayer::criticalAlert("************************");
		IOLayer::criticalAlert("************************");
		for (auto itr = m_warningMap.begin(); itr != m_warningMap.end(); itr++)
		{
			if (itr->second.empty())
				continue;
			IOLayer::warningAlert("Patient ID : " + itr->first+"\n");
			//do the same fix as above
			for each (Alerts var in itr->second)
			{
				IOLayer::warningAlert(var.toString());
			}
			IOLayer::warningAlert("----------------------");
		}
	}


	void AlertingUnit::checkLimits(PatientVitals vitals)
	{
		std::vector<Alerts> criticalVector;
		std::vector<Alerts> warningVector;
		Patient patient = m_patientList[vitals.patientId];
		for (auto i = vitals.vitals.begin(); i != vitals.vitals.end(); i++)
		{
			if (!compare(patient.devices[i->deviceId].validInputRange.min, patient.devices[i->deviceId].validInputRange.max, i->value))
			{
				criticalVector.push_back({ i->deviceId, i->value, "Device Malfunction : Value out of valid input range." });
				continue;
			}
			auto limit = patient.devices[i->deviceId].limits;
			for (auto j = limit.begin(); j != limit.end(); j++)
			{
				if (compare(j->range.min, j->range.max, i->value))
				{
					switch (j->type)
					{
					case Critical:
						criticalVector.push_back({ i->deviceId, i->value, j->message });
						break;
					case Warning:
						warningVector.push_back({ i->deviceId, i->value, j->message });
						break;
					case Normal:
						continue;
					default:
						criticalVector.push_back({ i->deviceId, i->value, "Unexpected Error : Undefined Type" });
						break;
					}
				}
			}
			m_criticalMap[vitals.patientId] = criticalVector;
			m_warningMap[vitals.patientId] = warningVector;
			alertUser();
		}

	}
}