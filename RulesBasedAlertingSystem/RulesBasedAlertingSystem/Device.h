#pragma once
#include <string>
#include <vector>

namespace RulesBasedAlertingSystem
{
	struct Range
	{
	public:
		double min;
		double max;
	};
	enum Type
	{
		Normal,
		Warning,
		Critical
	};

	struct Limits
	{
		Range range;
		Type type;
		std::string message;
	};
	struct Device
	{
		std::string deviceId;
		std::vector<Limits> limits;
	};
}
