#include "Sheet.h"

#include <xlnt/worksheet/column_properties.hpp>
#include <xlnt/worksheet/row_properties.hpp>

namespace Veridox::Private
{
	Sheet::Sheet(worksheet& sheet)
		: m_sheet{ sheet }
	{
	}

	void Sheet::SetColumnWidth(uint32_t column, double width)
	{
		auto& props = m_sheet.column_properties(column);
		
		props.width = width;
	}

	void Sheet::SetRowHeight(uint32_t row, double height)
	{
		auto& props = m_sheet.row_properties(row);

		props.height = height;
	}

	Cell Sheet::At(uint32_t column, uint32_t row)
	{
		cell c = m_sheet.cell(xlnt::column_t(column + 1), row);

		return Cell(c);
	}

	void Sheet::Set(uint32_t column, uint32_t row, uint32_t value, Style* style)
	{
		Cell cell = At(column, row);

		if (style != nullptr)
		{
			cell.SetStyle(*style, m_sheet);
		}

		cell.Set(value);
	}

	void Sheet::Set(uint32_t column, uint32_t row, const string& value, Style* style)
	{
		Cell cell = At(column, row);

		if (style != nullptr)
		{
			cell.SetStyle(*style, m_sheet);
		}

		cell.Set(value);
	}

	void Sheet::Set(uint32_t column, uint32_t row, datetime value, Style* style)
	{
		Cell cell = At(column, row);

		if (style != nullptr)
		{
			cell.SetStyle(*style, m_sheet);
		}

		cell.Set(value);
	}

	string Sheet::Name()
	{
		return m_sheet.title();
	}
}