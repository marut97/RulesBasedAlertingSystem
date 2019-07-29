// RulesBasedAlertingSystem.Host.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <string>
#include "../RulesBasedAlertingSystem/IOLayer.h"
#include "../RulesBasedAlertingSystem/ReceiverUnit.h"

int main()
{
	std::cout << "Hello World!!" << std::endl;
	RulesBasedAlertingSystem::IOLayer::warningAlert("Warning");
	RulesBasedAlertingSystem::IOLayer::criticalAlert("Critical");
	std::cout << "Hello World!!" << std::endl;

	std::map<std::string, RulesBasedAlertingSystem::Patient> map;
	RulesBasedAlertingSystem::Patient pat;
	pat.patientId = "abc";
	//auto devs = pat.devices;
	for (int i = 0; i <= 2; i++)
	{
		RulesBasedAlertingSystem::Device device;
		device.deviceId = 'x'+i;
		std::cout << device.deviceId << std::endl;
		RulesBasedAlertingSystem::Limits limits;
		limits.range.max = 100;
		limits.range.min = 0;
		limits.message = "Working";
		limits.type = RulesBasedAlertingSystem::Normal;
		device.limits.push_back(limits);
		pat.devices.insert({ device.deviceId, device });
	}
	map.insert({ pat.patientId, pat });
	RulesBasedAlertingSystem::SharedQueue queue;
	RulesBasedAlertingSystem::ReceiverUnit x(queue, map);

	RulesBasedAlertingSystem::PatientVitals vit;
	std::cout << std::endl /*<< x.unboxInput("{\"patientId\" : \"abc\" , \"x\" : 1.0 , \"y\" : 1.0, \"z\" : 1.0}", vit)*/ << "\t" << vit.patientId << "\t";
	std::cout << (int)vit.vitals.size() << std::endl;
	for (auto i = vit.vitals.begin(); i != vit.vitals.end(); ++i)
		std::cout << i->deviceId << "\t" << i->value << vit.vitals.size() << std::endl;

	RulesBasedAlertingSystem::IOLayer::readInput("as ");
	RulesBasedAlertingSystem::IOLayer::readMessage("as ");
	RulesBasedAlertingSystem::IOLayer::readInput("as ");
	RulesBasedAlertingSystem::IOLayer::readMessage("as ");
	RulesBasedAlertingSystem::IOLayer::readMessage("as ");
	RulesBasedAlertingSystem::IOLayer::readMessage("as ");


	//std::string line;
	//while (std::getline(std::cin, line)) // read from std::cin
	//{
	//	// show that it arrived
	//	std::cout << "Line Received: " << line << '\n';
	//}
    return 0;
}

