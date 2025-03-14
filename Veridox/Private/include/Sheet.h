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
		void SetColumnWidth(uint32_t column, double width) const;
		void SetRowHeight(uint32_t row, double height) const;

		Cell At(uint32_t column, uint32_t row) const;

		void Set(uint32_t column, uint32_t row, uint32_t value, Style* style = nullptr) const;
		void Set(uint32_t column, uint32_t row, const string& value, Style* style = nullptr) const;
		void Set(uint32_t column, uint32_t row, const datetime& value, Style* style = nullptr) const;

		uint32_t MakeCategory(const string& title) const;

		string Name() const;

	private:
		worksheet& m_sheet;

	};
}