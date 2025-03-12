#include "VAssert.h"

#include <stdexcept>

using std::runtime_error;

namespace Veridox
{
	void VAssert::IsTrue(bool condition, const string& message)
	{
		if(!condition)
		{
			throw(runtime_error(message));
		}
	}
}
