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

	void VAssert::IsTrue(ConditionalPredicate predicate, const string& message)
	{
		if(!predicate())
		{
			throw(runtime_error(message));
		}
	}
}
