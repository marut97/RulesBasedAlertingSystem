#include "ReceiverUnit.h"
#include "IOLayer.h"
#include "json11.hpp"

namespace RulesBasedAlertingSystem
{
	ReceiverUnit::ReceiverUnit(SharedQueue &queue, std::map<std::string, Patient> &map) : m_queue(queue), m_map(map)
	{
	}

	void ReceiverUnit::inputProcess() const
	{
		bool loopControl;
		do
		{
			std::string input = IOLayer::readVitals();
			loopControl = input.empty();
			if (!loopControl)
			{
				PatientVitals vitals;
				if(unboxInput(input, vitals))
					m_queue.enqueue(vitals);
			}
		} while (loopControl);
	}

	bool ReceiverUnit::unboxInput(const std::string& input, PatientVitals &vitals) const
	{
		json11::Json object = json11::Json::parse(input, std::string("Input not recieved"));

		if(object["patientId"].is_string())
			vitals.patientId = object["patientId"].string_value();
		else
		{
			IOLayer::warningAlert("Patient ID not provided");
			return false;
		}
		auto devs = m_map[vitals.patientId].devices;
		for (auto i = devs.begin(); i != devs.end(); i++)
		{
			Vitals temp;
			temp.deviceId = i->first;
			if (object[i->first].is_null())
			{
				IOLayer::warningAlert("Device Not Registered");
				return false;
			}
			else
			{
				if (object[i->first].is_number())
				{
					temp.value = object[i->first].number_value();
					vitals.vitals.push_back(temp);
					continue;
				}
				IOLayer::warningAlert("Device Value Not Acceptable, Device ID : "+ temp.deviceId);
				return false;
			}
		}
		return true;
	}
}
