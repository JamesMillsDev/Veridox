#pragma once

#include <string>
#include <stdexcept>

using std::runtime_error;
using std::string;

namespace Veridox
{
	typedef bool(*ConditionalPredicate)();

	class VAssert
	{
	public:
		template<typename T>
		static void IsNull(const T* actual, const string& message);
		template<typename T>
		static void IsNotNull(const T* actual, const string& message);

		template<typename T>
		static void AreEqual(const T& expected, const T& actual, const string& message);
		static void AreEqual(double expected, double actual, double tolerance, const string& message);
		static void AreEqual(float expected, float actual, float tolerance, const string& message);
		static void AreEqual(const char* expected, const char* actual, const string& message);
		static void AreEqual(const string& expected, const string& actual, const string& message);

		template<typename T>
		static void AreNotEqual(const T& expected, const T& actual, const string& message);
		static void AreNotEqual(double expected, double actual, double tolerance, const string& message);
		static void AreNotEqual(float expected, float actual, float tolerance, const string& message);
		static void AreNotEqual(const char* expected, const char* actual, const string& message);
		static void AreNotEqual(const string& expected, const string& actual, const string& message);

		static void IsTrue(bool condition, const string& message);
		static void IsTrue(ConditionalPredicate predicate, const string& message);

		static void IsFalse(bool condition, const string& message);
		static void IsFalse(ConditionalPredicate predicate, const string& message);

		static void Fail(const string& message);

	};

	template<typename T>
	inline void VAssert::IsNull(const T* actual, const string& message)
	{
		if (actual != nullptr)
		{
			throw(runtime_error(message));
		}
	}

	template<typename T>
	inline void VAssert::IsNotNull(const T* actual, const string& message)
	{
		if (actual == nullptr)
		{
			throw(runtime_error(message));
		}
	}

	template<typename T>
	inline void VAssert::AreEqual(const T& expected, const T& actual, const string& message)
	{
		if (expected != actual)
		{
			throw(runtime_error(message));
		}
	}

	template<typename T>
	inline void VAssert::AreNotEqual(const T& expected, const T& actual, const string& message)
	{
		if (expected == actual)
		{
			throw(runtime_error(message));
		}
	}
}