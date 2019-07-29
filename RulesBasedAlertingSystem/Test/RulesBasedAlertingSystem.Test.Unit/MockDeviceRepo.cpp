#include "MockDeviceRepo.h"

namespace RulesBasedAlertingSystem
{
	namespace Test
	{
		namespace Unit
		{
			bool RulesBasedAlertingSystem::Test::Unit::MockDeviceRepo::checkDeviceExist(std::string deviceId)
			{
				return{};
			}

			bool RulesBasedAlertingSystem::Test::Unit::MockDeviceRepo::registerNew(Device device)
			{
				return{};
			}

			bool RulesBasedAlertingSystem::Test::Unit::MockDeviceRepo::update(Device device)
			{
				return{};
			}

			bool RulesBasedAlertingSystem::Test::Unit::MockDeviceRepo::remove(std::string patientId)
			{
				return{};
			}

			RulesBasedAlertingSystem::Device RulesBasedAlertingSystem::Test::Unit::MockDeviceRepo::read(std::string deviceID)
			{
				return{};
			}

			std::vector<RulesBasedAlertingSystem::Device> RulesBasedAlertingSystem::Test::Unit::MockDeviceRepo::readAll()
			{
				return{};
			}
		}
	}
}
