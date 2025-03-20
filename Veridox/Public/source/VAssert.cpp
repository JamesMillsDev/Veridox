#include "VAssert.h"

namespace Veridox
{
	void VAssert::AreEqual(double expected, double actual, double tolerance, const string& message)
	{
		if (abs(expected) - abs(actual) > tolerance)
		{
			throw(runtime_error(message));
		}
	}

	void VAssert::AreEqual(float expected, float actual, float tolerance, const string& message)
	{
		if (fabsf(expected) - fabsf(actual) > tolerance)
		{
			throw(runtime_error(message));
		}
	}

	void VAssert::AreEqual(const char* expected, const char* actual, const string& message)
	{
		if (strcmp(expected, actual) != 0)
		{
			throw(runtime_error(message));
		}
	}

	void VAssert::AreEqual(const string& expected, const string& actual, const string& message)
	{
		if (expected != actual)
		{
			throw(runtime_error(message));
		}
	}

	void VAssert::AreNotEqual(double expected, double actual, double tolerance, const string& message)
	{
		if (abs(expected) - abs(actual) <= tolerance)
		{
			throw(runtime_error(message));
		}
	}

	void VAssert::AreNotEqual(float expected, float actual, float tolerance, const string& message)
	{
		if (fabsf(expected) - fabsf(actual) <= tolerance)
		{
			throw(runtime_error(message));
		}
	}

	void VAssert::AreNotEqual(const char* expected, const char* actual, const string& message)
	{
		if (strcmp(expected, actual) == 0)
		{
			throw(runtime_error(message));
		}
	}

	void VAssert::AreNotEqual(const string& expected, const string& actual, const string& message)
	{
		if (expected == actual)
		{
			throw(runtime_error(message));
		}
	}

	void VAssert::IsTrue(bool condition, const string& message)
	{
		if(!condition)
		{
			throw(runtime_error(message));
		}
	}

	void VAssert::IsTrue(ConditionalPredicate predicate, const string& message)
	{
		if(!predicate())
		{
			throw(runtime_error(message));
		}
	}

	void VAssert::IsFalse(bool condition, const string& message)
	{
		if (condition)
		{
			throw(runtime_error(message));
		}
	}

	void VAssert::IsFalse(ConditionalPredicate predicate, const string& message)
	{
		if (predicate())
		{
			throw(runtime_error(message));
		}
	}

	void VAssert::Fail(const string& message)
	{
		throw(runtime_error(message));
	}
}
