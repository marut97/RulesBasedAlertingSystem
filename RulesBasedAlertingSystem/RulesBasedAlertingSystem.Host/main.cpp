// RulesBasedAlertingSystem.Host.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <string>
#include "../RulesBasedAlertingSystem/IOLayer.h"
#include "../RulesBasedAlertingSystem/AlertingSystemModes.h"

int main()
{
	RulesBasedAlertingSystem::AlertingSystemModes alerting;
	alerting.displayModes();
    return 0;
}

