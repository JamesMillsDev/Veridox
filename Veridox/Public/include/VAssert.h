#pragma once

#include <string>

using std::string;

namespace Veridox
{
	class VAssert
	{
	public:
		static void IsTrue(bool condition, const string& message);

	};
}