#pragma once

#include <ctime>
#include <sstream>
#include <string>
#include <vector>

using std::ostream;
using std::string;
using std::stringstream;
using std::vector;

typedef bool(*TestFnc)(string& reason);
typedef void(*TestInitFnc)();
typedef void(*TestShutdownFnc)(int passCount, size_t maxTestCount);

class Veridox
{
	friend class ExcelHelper;

private:
	struct Test
	{
	public:
		const char* name;
		TestFnc test;

	};

	struct TestResult
	{
	public:
		const char* name;
		int id;
		bool success;
		string failReason;

	};

public:
	static void RegisterTest(Test fnc);
	static void SetTestInit(TestInitFnc fnc);
	static void SetTestShutdown(TestShutdownFnc fnc);
	static void Run();

private:
	static vector<Test> m_tests;
	static TestInitFnc m_init;
	static TestShutdownFnc m_shutdown;

private:
	static void OutputLog(int passCount, size_t testCount, stringstream& testLines, tm* dateTime);
	static void MakeHeader(string& header, bool isFileMode, int passCount, size_t testCount, tm* dateTime);

};

inline vector<Veridox::Test> Veridox::m_tests;

#pragma region Macros
#define TEST(FUNC_NAME) \
	bool Test##FUNC_NAME(string& reason); \
	struct TestStruct##FUNC_NAME { \
		TestStruct##FUNC_NAME() { Veridox::RegisterTest({#FUNC_NAME, Test##FUNC_NAME}); } \
	}; \
	TestStruct##FUNC_NAME testStruct##FUNC_NAME; \
	bool Test##FUNC_NAME(string& reason)

#define TEST_INIT(FUNC_NAME) \
	void Test##FUNC_NAME(); \
	struct TestStruct##FUNC_NAME { \
		TestStruct##FUNC_NAME() { Veridox::SetTestInit(Test##FUNC_NAME); } \
	}; \
	TestStruct##FUNC_NAME testStruct##FUNC_NAME; \
	void Test##FUNC_NAME()

#define TEST_SHUTDOWN(FUNC_NAME) \
	void Test##FUNC_NAME(int passCount, size_t maxTestCount); \
	struct TestStruct##FUNC_NAME { \
		TestStruct##FUNC_NAME() { Veridox::SetTestShutdown(Test##FUNC_NAME); } \
	}; \
	TestStruct##FUNC_NAME testStruct##FUNC_NAME; \
	void Test##FUNC_NAME(int passCount, size_t maxTestCount)

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <cstdlib>

#ifndef VERIDOX_MAIN
#define VERIDOX_MAIN \
	int main() { \
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);\
		Veridox::Run();\
		return 0; \
	} 
#else
#define VERIDOX_MAIN \
	int main() { \
		Veridox::Run();\
		return 0; \
	}
#endif  
#pragma endregion  
#endif //