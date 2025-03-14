#pragma once

#include <xlnt/worksheet/worksheet.hpp>

#include "Cell.h"

using xlnt::worksheet;

namespace Veridox::Private
{
	class Sheet
	{
	public:
		Sheet(worksheet& sheet);

	public:
		void SetColumnWidth(uint32_t column, double width);
		void SetRowHeight(uint32_t row, double height);

		Cell At(uint32_t column, uint32_t row);

		void Set(uint32_t column, uint32_t row, uint32_t value, Style* style = nullptr);
		void Set(uint32_t column, uint32_t row, const string& value, Style* style = nullptr);
		void Set(uint32_t column, uint32_t row, datetime value, Style* style = nullptr);

		string Name();

	private:
		worksheet& m_sheet;

	};
}