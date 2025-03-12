#include "Veridox.h"

#include <format>
#include <iomanip>
#include <iostream>

using std::runtime_error;

namespace Veridox
{
	TestInitFnc Veridox::m_init;
	TestShutdownFnc Veridox::m_shutdown;

	void GetLocalTime(tm* outTime, const time_t* inTime)
	{
#if defined(_MSC_VER)  // MSVC
		(void)localtime_s(outTime, inTime);
#else  // GCC, Clang
		(void)localtime_r(inTime, outTime);
#endif
	}

	void Veridox::RegisterTest(Test fnc)
	{
		m_tests.emplace_back(fnc);
	}

	void Veridox::SetTestInit(TestInitFnc fnc)
	{
		m_init = fnc;
	}

	void Veridox::SetTestShutdown(TestShutdownFnc fnc)
	{
		m_shutdown = fnc;
	}

	void Veridox::Run()
	{
		if (m_init != nullptr)
		{
			m_init();
		}

		int passed = 0;

		for (int i = 0; i < static_cast<int>(m_tests.size()); ++i)
		{
			string reason;

			auto& [name, test] = m_tests[i];

			bool succeeded = false;

			try
			{
				test();
				succeeded = true;
			}
			catch (runtime_error& e)
			{
				reason = e.what();
			}

			TestResult state =
			{
				name, i + 1, succeeded, reason
			};

			OutputTest(std::cout, false, state);

			if (succeeded)
			{
				passed++;
			}
		}

		std::cout << std::format("\n\x1B[33m{} out of {} tests passed!\x1B[37m\n", passed, m_tests.size());

		if (m_shutdown != nullptr)
		{
			m_shutdown(passed, m_tests.size());
		}
	}

	void Veridox::OutputTest(ostream& stream, bool isFileStream, TestResult& state)
	{
		stream << std::format(
			"{}Test {:0>3} {}{:12} {:18}{} {}\n",
			(isFileStream ? "" : "\x1B[33m"),
			state.id, (isFileStream ? "" : "\x1B[36m"),
			state.name, (isFileStream ? state.success ? "Successful" : "Failed" : state.success ? "\x1B[32mSuccessful" : "\x1B[31mFailed"),
			(isFileStream ? "" : "\x1B[37m"),
			(state.success ? "" : string("Reason: ") + state.failReason));
	}

	//void Veridox::OutputLog(int passCount, size_t testCount, stringstream& testLines, tm* dateTime)
	//{
	//	fstream stream;
	//
	//	stream.open("tests.log", std::ios::out | std::ios::app);
	//
	//	if (stream.is_open())
	//	{
	//		string header;
	//		MakeHeader(header, true, passCount, testCount, dateTime);
	//
	//		stream << header << testLines.str();
	//	}
	//
	//	stream.close();
	//}
	//
	//void Veridox::MakeHeader(string& header, bool isFileMode, int passCount, size_t testCount, tm* dateTime)
	//{
	//	stringstream stream;
	//
	//	if (!isFileMode)
	//	{
	//		stream << "\x1B[36m";
	//	}
	//
	//	stream << "====================================================\n";
	//	stream << "Date: " << std::put_time(dateTime, "%d/%m/%Y");
	//	stream << " Time: " << std::put_time(dateTime, "%H:%M:%S");
	//
	//	if (isFileMode)
	//	{
	//		float successRate = static_cast<float>(passCount) / static_cast<float>(testCount);
	//		successRate *= 100.f;
	//
	//		stream << " Successful: ";
	//		stream << std::setprecision(2) << std::fixed << successRate << "%";
	//	}
	//
	//	stream << "\n====================================================\n";
	//
	//	header = stream.str();
	//}
}