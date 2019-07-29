#include "IOLayer.h"
#include "iostream"
#include <windows.h>
#include <stdlib.h>

namespace RulesBasedAlertingSystem
{
	std::string IOLayer::readInput(std::string menu)
	{
		std::cout << menu << std::endl;
		std::string input;
		std::cin >> input;
		return input;
	}

	std::string IOLayer::readMessage(std::string menu)
	{
		std::cout << menu << std::endl;
		std::cin.ignore();
		std::string input;
		std::getline(std::cin, input);
		return input;
	}

	std::string IOLayer::readDevices(std::string menu, int deviceSize)
	{
		std::cout << menu << std::endl;
		std::string input;
		std::cin >> input;
		return input;
	}

	void IOLayer::display(std::string output)
	{
		std::cout << output << std::endl;

	}

	std::string IOLayer::readVitals()
	{
		std::string input;
		std::getline(std::cin, input);
		return input;
	}

	void IOLayer::criticalAlert(std::string input)
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, 12);
		std::cout << input << std::endl;
		SetConsoleTextAttribute(hConsole, 7);
	}

	void IOLayer::warningAlert(std::string input)
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, 14);
		std::cout << input << std::endl;
		SetConsoleTextAttribute(hConsole, 7);
	}
	void IOLayer::clearScreen()
	{
		system("CLS");
	}
}