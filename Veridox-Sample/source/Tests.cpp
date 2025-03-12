#include "VAssert.h"
#include "Veridox.h"

TEST(Banana)
{
	Veridox::VAssert::IsTrue(false, "Test failure");
}

TEST(Banana2)
{
	Veridox::VAssert::IsTrue(true, "Test failure");
}

VERIDOX_MAIN