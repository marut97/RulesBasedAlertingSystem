#include "DeviceRegistrationUnit.h"
#include "AlertingSystemModes.h"
#include "IDeviceRepository.h"

#include "Device.h"
#include "IOLayer.h"
#include<iostream>
#include<string>
using namespace std;
namespace RulesBasedAlertingSystem
{
	DeviceRegistrationUnit::DeviceRegistrationUnit(IDeviceRepository &deviceRepo) : m_deviceRepository(deviceRepo)
	{
	}

	void DeviceRegistrationUnit::readInput()
	{
		bool loopControl;
		do
		{
			string input = IOLayer::readInput("Select \n1.New Device Registration   \n2.Update Registered Device  \n3.Delete Registered Device \n4.Read Device using DeviceID  \n5.Read All Devices  \n6.Exit");
			try
			{			
				loopControl = opartationInDeviceRegistration(stoi(input));
			}
			catch (...)
			{
				IOLayer::criticalAlert("Invalid input.  Try again... ");
				loopControl = true;
			}
			IOLayer::pause();
			IOLayer::clearScreen();
		} while (loopControl);
	}

	bool DeviceRegistrationUnit::opartationInDeviceRegistration(int operation)
	{
		switch (operation)
		{
		case 1:registerDevice();

			break;
		case 2:updateRegisteredDevices();
			break;
		case 3:deleteRegisteredDevice();
			break;
		case 4:readRegisteredDevice();
			break;
		case 5:readAllRegisteredDevices();
			break;
		case 6:
			return false;
		default:
			IOLayer::criticalAlert("Invalid input.  Try again... ");
			break;
		}
		return true;
	}

	Range DeviceRegistrationUnit::getValidLimitsRange()
	{
		Range range;
		bool validRangeFlag;
		string inputRange;
		//To check valid range
		do
		{
			validRangeFlag = true;
			inputRange = IOLayer::readInput("Enter valid Input Range for the Device\n Min Range : ");

			while (1)
			{
				try
				{
					range.min = stod(inputRange);
					break;
				}
				catch (...)
				{
					IOLayer::criticalAlert("Invalid input.  Try again... ");
					inputRange = IOLayer::readInput("");
				}
			}

			inputRange = IOLayer::readInput(" Max Range : ");

			while (1)
			{
				try
				{
					range.max = stod(inputRange);
					break;
				}
				catch (...)
				{
					IOLayer::criticalAlert("Invalid input.  Try again... ");
					inputRange = IOLayer::readInput("");
				}
			}

			if (range.min >= range.max)
			{
				
				IOLayer::criticalAlert("Invalid input.  Try again... ");
				validRangeFlag = false;
			}
		} while (!validRangeFlag);

		return range;
	}

	vector<Limits> DeviceRegistrationUnit::getLimits(Range range)
	{

		double max;
		vector<Limits> limits;
		limits.clear();
		Limits limit;
		bool validRangeFlag;
		string inputRange;
		

		double min = range.min;

		do {

			
			do {
				validRangeFlag = true;
				inputRange = IOLayer::readInput("Enter the  sub range starting from "+to_string(min)+" to ");
				while (1)
				{
					try
					{
						max = stod(inputRange);
						break;
					}
					catch (...)
					{
						IOLayer::criticalAlert("Invalid input.  Try again... ");
						inputRange = IOLayer::readInput("");
					}
				}


				if (max > range.max || max<=min)
				{
					IOLayer::criticalAlert("Invalid input.  Try again... ");
					validRangeFlag = false;
				}
			} while (!validRangeFlag);


			limit.range.min = min;
			limit.range.max = max;

			min = max;

			limit.type = getTypeOfRange();
			limit.message= getMessage();


		
			limits.push_back(limit);
			
		} while (max < range.max);

		return limits;
	}


	Type DeviceRegistrationUnit::getTypeOfRange()
	{
		bool validRangeFlag;
		Type type;
		int rangeType;
		do {

			validRangeFlag = true;


			string inputType = IOLayer::readInput("Enter type of Range . \n1.Normal  \n2.Warning  \n3.Critical");

			while (true)
			{
				try
				{
					rangeType = stoi(inputType);
					break;
				}
				catch (...)
				{
					IOLayer::criticalAlert("Invalid input.  Try again... ");
					inputType = IOLayer::readInput("");
				}
			}
	
			if (rangeType == 1)
			{
				type=Normal;
				
				break;
			}
			else if (rangeType == 2)
			{
				type=Warning;
				
				break;
			}
			else if (rangeType == 3)
			{
				type=Critical;
				
				break;
			}
			else
			{
				IOLayer::criticalAlert("Invalid input.  Try again... ");
				validRangeFlag = false;
			}
		} while (!validRangeFlag);

		return type;
		
	}
	std::string DeviceRegistrationUnit::getMessage()
	{
		string message = IOLayer::readMessage("Enter the message for type :");
		return message;

	}


	void DeviceRegistrationUnit::registerDevice()
	{
		Device newDevice;
		newDevice.deviceId = IOLayer::readInput("Enter Device ID : ");
		
		if (m_deviceRepository.checkDeviceExist(newDevice.deviceId))
		{
			IOLayer::criticalAlert("Device Id already Exist");
			return;
		}


		newDevice.validInputRange = getValidLimitsRange();

		newDevice.limits = getLimits(newDevice.validInputRange);

		if (m_deviceRepository.registerNew(newDevice))
		{

			IOLayer::warningAlert("Device successfully registered");
		}
		else
		{
			IOLayer::criticalAlert("Device registration failed");
		}
		
		
	}

	void DeviceRegistrationUnit::updateRegisteredDevices()
	{
		
		Device updateDevice;

		updateDevice.deviceId = IOLayer::readInput("Enter Device ID : ");
		if (!m_deviceRepository.checkDeviceExist(updateDevice.deviceId))
		{
			IOLayer::criticalAlert("Device Id does not Exist");
			return;
		}

		updateDevice.validInputRange = getValidLimitsRange();

		updateDevice.limits = getLimits(updateDevice.validInputRange);

		if (m_deviceRepository.registerNew(updateDevice))
		{
			IOLayer::warningAlert("Device successfully updated");
		}
		else
		{
			IOLayer::criticalAlert("Device updation failed");
		}

	}

	void DeviceRegistrationUnit::readAllRegisteredDevices()
	{
		vector<Device> devicesList;

		devicesList.clear();
		devicesList = m_deviceRepository.readAll();
		for (auto i = devicesList.begin(); i != devicesList.end(); i++)
			IOLayer::display(i->toString());
		/*if (devicesList.size() == 0)
		{
			IOLayer::criticalAlert("No Device found");
		}
		else
		{
			for(Device device:devicesList)
			{
				IOLayer::warningAlert("\n\nDevice Id : "+ device.deviceId);
				IOLayer::warningAlert("Device Vaild input range : "+to_string(device.validInputRange.min)+" to "+to_string(device.validInputRange.max));
				for (int i = 0; i < device.limits.size(); i++)
				{
					IOLayer::warningAlert("Type : "+ getEnumTypeName(device.limits[i].type)+ " Range :"+to_string(device.limits[i].range.min)+" to "+to_string(device.limits[i].range.max));
					IOLayer::warningAlert("Message : "+ device.limits[i].message);
				}

				
			}
		}*/

	}

	void DeviceRegistrationUnit::readRegisteredDevice()
	{
		string deviceId = IOLayer::readInput("Enter Device ID : ");
		
		Device device = (m_deviceRepository.read(deviceId));
		IOLayer::display(device.toString());

		/*if (device.deviceId == "")
		{
			IOLayer::criticalAlert("Device Id not found");
		}
		else
		{
			string enumName;
			IOLayer::warningAlert("Device Id : " + device.deviceId);
			IOLayer::warningAlert("Device Vaild input range : " + to_string(device.validInputRange.min) + " to " + to_string(device.validInputRange.max));
			for (int i = 0; i < device.limits.size(); i++)
			{
				
				

				IOLayer::warningAlert("Type : " + getEnumTypeName(device.limits[i].type) + " Range :" + to_string(device.limits[i].range.min) + " to " + to_string(device.limits[i].range.max));
				IOLayer::warningAlert("Message : " + device.limits[i].message);
			}
		}
*/
	}
	void DeviceRegistrationUnit::deleteRegisteredDevice()
	{
		string deviceId = IOLayer::readInput("Enter Device ID : ");
		
		if (m_deviceRepository.remove(deviceId))
		{
			IOLayer::warningAlert("Device Id " + deviceId + " successfully deleted");
		}
		else
		{
			IOLayer::criticalAlert("Deletion is failed");
		}
	}


	string DeviceRegistrationUnit::getEnumTypeName(int value)
	{
		if (value == 0)
			return "Normal";
		else if (value == 1)
			return "Warning";
		else
			return "Critical";

	}
}

	

