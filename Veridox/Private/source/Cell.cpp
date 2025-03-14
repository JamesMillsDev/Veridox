#include "Cell.h"

#include <xlnt/worksheet/worksheet.hpp>

namespace Veridox::Private
{
	Cell::Cell(uint32_t column, uint32_t row, worksheet ws)
		: column{ column }, row{ row }, m_cell{ ws.cell(xlnt::column_t(column), row) }
	{
	}

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

	void Cell::SetStyle(Style& style)
	{
		xlnt::style s = style.ToExcel(m_cell.style());

		m_cell.style(s);
	}
}