#include "PatientRegistrationUnit.h"
#include "AlertingSystemModes.h"
#include "IOLayer.h"

namespace RulesBasedAlertingSystem
{
	PatientRegistrationUnit::PatientRegistrationUnit(IPatientRepository &patientRepo, IDeviceRepository &deviceRepo) : m_patientRepo(patientRepo), m_deviceRepo(deviceRepo)
	{
	}
	void PatientRegistrationUnit::readInput()
	{
		generateDeviceList();
		bool loopControl;
		do
		{
			std::string input = IOLayer::readInput("Select \n1.New Patient Registration   \n2.Update Registered Patient  \n3.Delete Registered Patient \n4.Read Patient using PatientID  \n5.Read All Patients  \n6.Exit");
			try
			{
				loopControl = operationInPatientRegistration(stoi(input));
			}
			catch (...)
			{
				IOLayer::criticalAlert("Invalid input.  Try again... ");
			}
			IOLayer::clearScreen();
		} while (loopControl);
	}
	void PatientRegistrationUnit::generateDeviceList()
	{
		auto deviceList = m_deviceRepo.readAll();
		for (auto i = deviceList.begin(); i != deviceList.end(); i++)
		{
			m_deviceList.insert({ i->deviceId, *i });
		}
	}
	void PatientRegistrationUnit::updateRegisteredPatients()
	{
		std::string patientID = IOLayer::readInput("Enter Patient ID : ");
		if (!m_patientRepo.checkPatientExists(patientID))
		{
			IOLayer::criticalAlert("Patient doesn't exist");
			return;
		}
		else
		{
			Patient patient = m_patientRepo.read(patientID);
			bool loopControl;
			std::string menu;
			do
			{
				std::string input = IOLayer::readInput("1. Register New Device \n2. Update Registered Device \nAny other key to exit..");
				if (stoi(input) == 1)
				{
					menu.append("Enter Device ID : \nAvailable Devices are :\n");
					for (auto i = m_deviceList.begin(); i != m_deviceList.end(); i++)
					{
						menu.append(i->first + "\n");
					}
					menu.append("0 to exit...\n");
					std::string deviceID = IOLayer::readDevices(menu, m_deviceList.size());
					if (stoi(deviceID) == 0)
						loopControl = false;
					else if (m_deviceList.find(deviceID) == m_deviceList.end())
					{
						IOLayer::criticalAlert("Device Does not exist. Try Again\n");
						loopControl = true;
					}
					else if (patient.devices.find(deviceID) != patient.devices.end())
					{
						IOLayer::criticalAlert("Device Already registered. Try Again\n");
						loopControl = true;
					}
					else
					{
						loopControl = true;
						auto device = registerDevice(deviceID);
						patient.devices.insert({ device.deviceId,device });
					}
				}
				else if (stoi(input) == 2)
				{
					menu.append("Enter Device ID : \nAvailable Devices are :\n");
					for (auto i = m_deviceList.begin(); i != m_deviceList.end(); i++)
					{
						menu.append(i->first + "\n");
					}
					menu.append("0 to exit...\n");
					std::string deviceID = IOLayer::readDevices(menu, m_deviceList.size());
					if (stoi(deviceID) == 0)
						loopControl = false;
					else if (m_deviceList.find(deviceID) == m_deviceList.end())
					{
						IOLayer::criticalAlert("Device Does not exist. Try Again\n");
						loopControl = true;
					}
					else if (patient.devices.find(deviceID) == patient.devices.end())
					{
						IOLayer::criticalAlert("Device Not registered. Try Again\n");
						loopControl = true;
					}
					else
					{
						loopControl = true;
						patient.devices.erase(deviceID);
						auto device = registerDevice(deviceID);
						patient.devices.insert({ device.deviceId,device });
					}
				}
			}
			while (loopControl);
		}
	}
	void PatientRegistrationUnit::readAllRegisteredPatients()
	{
		auto patients = m_patientRepo.readAll();
		for (auto i = patients.begin(); i != patients.end(); i++)
			IOLayer::display(i->toString());
	}
	void PatientRegistrationUnit::readRegisteredPatients()
	{
		std::string patientId = IOLayer::readInput("Enter Patient ID");
		IOLayer::display(m_patientRepo.read(patientId).toString());
	}
	void PatientRegistrationUnit::deleteRegisteredPatient()
	{
		std::string patientId = IOLayer::readInput("Enter Patient ID");
		if (m_patientRepo.remove(patientId))
			IOLayer::display("Removal Successful");
		else
			IOLayer::display("RemovalUnsuccessful");
	}
	void PatientRegistrationUnit::registerPatient()
	{
		Patient newPatient;
		newPatient.patientId = IOLayer::readInput("Enter Patient ID : ");
		if (m_patientRepo.checkPatientExists(newPatient.patientId))
		{
			IOLayer::criticalAlert("Patient Id already Exists");
			return;
		}
		bool loopControl;
		do
		{
			std::string menu;
			menu.append("Enter Device ID : \nRegistered Devices are :\n");
			for (auto i = m_deviceList.begin(); i != m_deviceList.end(); i++)
			{
				menu.append(i->first + "\n");
			}
			menu.append("0 to exit...\n");
			std::string deviceID = IOLayer::readDevices(menu, m_deviceList.size());
			if (stoi(deviceID) == 0)
				loopControl = false;
			else if (m_deviceList.find(deviceID) == m_deviceList.end())
			{
				IOLayer::criticalAlert("Device Does not exist. Try Again\n");
				loopControl = true;
			}
			else if (newPatient.devices.find(deviceID) != newPatient.devices.end())
			{
				IOLayer::criticalAlert("Device Already registered. Try Again\n");
				loopControl = true;
			}
			else
			{
				loopControl = true;
				auto device = registerDevice(deviceID);
				newPatient.devices.insert({ device.deviceId,device });
			}

		}
		while (loopControl);
	}

	RulesBasedAlertingSystem::Device RulesBasedAlertingSystem::PatientRegistrationUnit::registerDevice(
		std::string deviceID)
	{
		Device newDevice;
		newDevice.deviceId = deviceID;
		std::string input = IOLayer::readInput("Do you want to set custom ranges for the device?\n(y/n)\n");
		if (input == "y" || input == "Y")
		{
			newDevice.validInputRange = DeviceRegistrationUnit::getValidLimitsRange();
			newDevice.limits = DeviceRegistrationUnit::getLimits(newDevice.validInputRange);
			return newDevice;
		}
			return m_deviceList[deviceID];
	}
	bool PatientRegistrationUnit::operationInPatientRegistration(int operation)
	{
		switch (operation)
		{
		case 1:registerPatient();
			break;
		case 2:updateRegisteredPatients();
			break;
		case 3:deleteRegisteredPatient();
			break;
		case 4:readRegisteredPatients();
			break;
		case 5:readAllRegisteredPatients();
			break;
		case 6:
			return false;
		default:
			IOLayer::criticalAlert("Invalid input.  Try again... ");
			break;
		}
		return true;
	}
}