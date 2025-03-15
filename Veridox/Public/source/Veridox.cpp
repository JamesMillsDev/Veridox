#include "Veridox.h"

#include <format>
#include <iomanip>
#include <iostream>

#include "Excel.h"
#include "Style.h"

using std::exception;

namespace Veridox
{
	using Private::Excel;
	using Private::Styles;

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

		Styles::Init();

		Excel* excel = new Excel("tests.xlsx");

		excel->Open();

		const uint32_t idCategory = excel->MakeCategory("ID", 5.00);
		const uint32_t nameCategory = excel->MakeCategory("Name", 30.00);
		const uint32_t resultCategory = excel->MakeCategory("Result", 15.00);
		const uint32_t messageCategory = excel->MakeCategory("Message", 150.00);

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
			catch (exception& e)
			{
				reason = e.what();
			}

			TestResult state =
			{
				name, i + 1, succeeded, reason
			};

			OutputTest(std::cout, false, state);

			excel->Set(idCategory, i + 2, i + 1, Styles::id[i % 2]);
			excel->Set(nameCategory, i + 2, name, Styles::normalBody[i % 2]);
			excel->Set(resultCategory, i + 2, state.success ? "Succeeded" : "Failed", state.success ? Styles::succeeded : Styles::failed);
			excel->Set(messageCategory, i + 2, state.failReason, Styles::normalBody[i % 2]);

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
		
		excel->Close();

		Styles::Shutdown();

		delete excel;
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
}