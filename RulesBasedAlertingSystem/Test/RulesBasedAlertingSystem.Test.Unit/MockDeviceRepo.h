#pragma once
#include "../../RulesBasedAlertingSystem/IDeviceRepository.h"

namespace RulesBasedAlertingSystem
{
	namespace Test
	{
		namespace Unit
		{
			class MockDeviceRepo : public IDeviceRepository
			{
				bool checkDeviceExist(std::string deviceId) override;
				bool registerNew(Device device) override;
				bool update(Device device) override;
				bool remove(std::string patientId) override;
				Device read(std::string deviceID) override;
				std::vector<Device> readAll() override;
			};
		}
	}
}