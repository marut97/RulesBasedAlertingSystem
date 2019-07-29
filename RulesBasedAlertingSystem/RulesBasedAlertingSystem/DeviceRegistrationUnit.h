#pragma once
#include "IDeviceRepository.h"
#include <string>

namespace RulesBasedAlertingSystem
{

	class DeviceRegistrationUnit
	{
		void updateRegisteredDevices();   
		void readAllRegisteredDevices();
		void readRegisteredDevice();
		void deleteRegisteredDevice();
		void registerDevice();
		bool opartationInDeviceRegistration(int operation);
		std::string getEnumTypeName(int);

	public:		
		DeviceRegistrationUnit(IDeviceRepository &deviceRepo);
		void readInput();
		static std::vector<Limits> getLimits(Range range);
		static Range getValidLimitsRange();
		static std::string getMessage();
		static Type getTypeOfRange();

	private:
		IDeviceRepository &m_deviceRepository;

	};
}
