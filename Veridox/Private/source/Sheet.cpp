#include "Sheet.h"

#include <xlnt/worksheet/column_properties.hpp>
#include <xlnt/worksheet/row_properties.hpp>

namespace Veridox::Private
{
	uint32_t categoryIndex = 0;

	Sheet::Sheet(worksheet& sheet)
		: m_sheet{ sheet }
	{
	}

	void Sheet::SetColumnWidth(const uint32_t column, const double width) const
	{
		auto& props = m_sheet.column_properties(column);
		
		props.width = width;
	}

	void Sheet::SetRowHeight(const uint32_t row, const double height) const
	{
		auto& props = m_sheet.row_properties(row);

		props.height = height;
	}

	Cell Sheet::At(const uint32_t column, const uint32_t row) const
	{
		cell c = m_sheet.cell(xlnt::column_t(column + 1), row);

		return { c };
	}

	void Sheet::Set(const uint32_t column, const uint32_t row, const uint32_t value, Style* style) const
	{
		Cell cell = At(column, row);

		if (style != nullptr)
		{
			cell.SetStyle(*style, m_sheet);
		}

		cell.Set(value);
	}

	void Sheet::Set(const uint32_t column, const uint32_t row, const string& value, Style* style) const
	{
		Cell cell = At(column, row);

		if (style != nullptr)
		{
			cell.SetStyle(*style, m_sheet);
		}

		cell.Set(value);
	}

	void Sheet::Set(const uint32_t column, const uint32_t row, const datetime& value, Style* style) const
	{
		Cell cell = At(column, row);

		if (style != nullptr)
		{
			cell.SetStyle(*style, m_sheet);
		}

		cell.Set(value);
	}

	uint32_t Sheet::MakeCategory(const string& title) const
	{
		const uint32_t column = categoryIndex++;

		Set(column, 1, title, &Styles::title);

		return column;
	}

	string Sheet::Name() const
	{
		return m_sheet.title();
	}
}