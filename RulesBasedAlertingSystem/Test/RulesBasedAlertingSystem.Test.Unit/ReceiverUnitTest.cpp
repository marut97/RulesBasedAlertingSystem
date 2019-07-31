#include "gtest\gtest.h"
#include "../../RulesBasedAlertingSystem/ReceiverUnit.h"
#include "MockInputOutput.h"
#include "MockPatientRepo.h"
#include <windows.h>

namespace RulesBasedAlertingSystem
{
	namespace Test
	{
		namespace Unit
		{
			class ReceiverUnitTest : public ::testing::Test
			{
				
			};

			TEST_F(ReceiverUnitTest, ValidInputTest)
			{
				SharedQueue queue;
				std::map<std::string, Patient> map;
				
				MockPatientRepo repo;
				auto patients = repo.readAll();
				for (auto i = patients.begin(); i != patients.end(); i++)
					map.insert({i->patientId, *i});
				MockInputOutput inOut;
				ReceiverUnit receiver(queue, map, inOut);

				std::thread receiverThread(&ReceiverUnit::inputProcess, &receiver);

				std::this_thread::sleep_for(std::chrono::seconds(5));
				//receiverThread.join();
				ASSERT_EQ(queue.isEmpty(), false);
				auto data = queue.dequeue();
				ASSERT_EQ(data.patientId, "11");
				ASSERT_EQ(data.vitals.size(), 3);
				data = queue.dequeue();
				data = queue.dequeue();
				ASSERT_EQ(queue.isEmpty(), true);
				ASSERT_EQ(TerminateThread(receiverThread.native_handle(), 0),1);
				//receiverThread.join();
				//receiverThread.detach();
				std::terminate();
			}
		}
	}
}
