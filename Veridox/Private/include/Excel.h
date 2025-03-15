#pragma once

#include <map>
#include <string>

#include <xlnt/styles/style.hpp>
#include <xlnt/workbook/workbook.hpp>
#include <xlnt/worksheet/worksheet.hpp>

using std::map;
using std::string;

using xlnt::style;
using xlnt::workbook;
using xlnt::worksheet;

namespace Veridox::Private
{
	class Style;

	class Excel
	{
	public:
		Excel(string wbName);

	public:
		void Open();
		void Close() const;

		void Set(uint32_t column, uint32_t row, uint32_t value, Style* style = nullptr);
		void Set(uint32_t column, uint32_t row, string value, Style* style = nullptr);

		uint32_t MakeCategory(const string& id, double width);

	private:
		workbook* m_workbook;
		worksheet m_worksheet;
		string m_workbookName;

		map<string, style*> m_cachedStyles;

	};
}