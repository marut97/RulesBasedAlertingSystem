#include "gtest\gtest.h"
#include "../../RulesBasedAlertingSystem/SharedQueue.h"
namespace RulesBasedAlertingSystem
{
	namespace Test
	{
		namespace Unit
		{
			class SharedQueueTest : public ::testing::Test
			{

			};
			TEST(SharedQueueTest, abc1)
			{
				PatientVitals vitals;
				vitals.patientId = "123";
				SharedQueue sq;
				EXPECT_EQ(sq.isEmpty(), true);
				sq.enqueue(vitals);
				EXPECT_EQ(sq.isEmpty(), false);
				PatientVitals testvitals = sq.dequeue();
				EXPECT_EQ(testvitals.patientId, vitals.patientId);

				//EXPECT_EQ(sq.dequeue(), vitals);
				EXPECT_EQ(sq.isEmpty(), true);

			}
		}
	}
}