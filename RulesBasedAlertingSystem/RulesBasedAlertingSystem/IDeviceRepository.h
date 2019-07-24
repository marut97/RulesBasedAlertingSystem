#pragma once
#include "AlertingUnit.h"
#include "Alerts.h"
#include "Device.h"
#include "Patient.h"
#include "PatientVitals.h"
#include <string.h>
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