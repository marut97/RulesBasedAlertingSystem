#pragma once
#include "Device.h"
#include "PatientVitals.h"

namespace RulesBasedAlertingSystem{
class IDeviceRepository
{
	public: virtual ~IDeviceRepository() {}
	public: virtual bool Register(Device device);
	public: virtual bool Update(Device device);
	public: virtual Device Read(std::string deviceID);
	public: virtual std::vector<Device> ReadAll();
};
}