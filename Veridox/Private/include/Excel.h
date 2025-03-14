#pragma once

#include <list>
#include <string>

#include <xlnt/workbook/workbook.hpp>

#include "Sheet.h"

using std::list;
using std::string;

using xlnt::workbook;

namespace Veridox::Private
{
	class Excel
	{
	public:
		Excel(const string& wbName);

	public:
		void Open();
		void Close();

		Sheet* GetSheet(const string& name);

	private:
		workbook* m_workbook;
		string m_workbookName;

		list<Sheet*> m_sheets;

	};
}