#include "MockInputOutput.h"

namespace RulesBasedAlertingSystem
{
	namespace Test
	{
		namespace Unit
		{
			std::string MockInputOutput::readInput(std::string menu)
			{
				return{};
			}

			std::string MockInputOutput::readMessage(std::string menu)
			{
				return{};
			}

			std::string MockInputOutput::readVitals()
			{
				return{};
			}

			void MockInputOutput::pause()
			{
				return;
			}

			void MockInputOutput::display(std::string output)
			{
				return;
			}

			void MockInputOutput::criticalAlert(std::string input)
			{
				return;
			}

			void MockInputOutput::warningAlert(std::string input)
			{
				return;
			}

			void MockInputOutput::clearScreen()
			{
				return;
			}
		}
	}

}