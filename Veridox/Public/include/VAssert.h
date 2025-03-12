#pragma once

#include <string>

using std::string;

namespace Veridox
{
	typedef bool(*ConditionalPredicate)();

	class VAssert
	{
	public:
		static void IsTrue(bool condition, const string& message);
		static void IsTrue(ConditionalPredicate predicate, const string& message);

	};
}