#include "VAssert.h"
#include "Veridox.h"

using Veridox::VAssert;

TEST(ConditionalAssertionFailure)
{
	VAssert::IsTrue(false, "Test failure");
}

TEST(ConditionalAssertionSuccess)
{
	VAssert::IsTrue(true, "Test success");
}

TEST(PredicateAssertionFailure)
{
	auto pred = []() { return false; };

	VAssert::IsTrue(pred, "Test failure");
}

TEST(PredicateAssertionSuccess)
{
	auto pred = []() { return true; };

	VAssert::IsTrue(pred, "Test success");
}

VERIDOX_MAIN