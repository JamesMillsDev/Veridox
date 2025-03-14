#include "Cell.h"

#include <xlnt/worksheet/worksheet.hpp>
#include <xlnt/workbook/workbook.hpp>

using xlnt::workbook;

namespace Veridox::Private
{
	Cell::Cell(cell& cell)
		: column{ cell.column_index() }, row{ cell.row() }, m_cell{ cell }
	{
	}

	void Cell::Set(uint32_t value)
	{
		m_cell.value(value);
	}

	void Cell::Set(const string& value)
	{
		m_cell.value(value);
	}

	void Cell::Set(datetime value)
	{
		m_cell.value(value);
	}

	void Cell::SetStyle(Style& style, worksheet& sheet)
	{
		workbook book = sheet.workbook();

		if (!book.has_style(style.name))
		{
			book.create_style(style.name);
		}

		m_cell.style(style.ToExcel(book.style(style.name)));
	}
}