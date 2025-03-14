#include "CellAlignment.h"

namespace Veridox::Private
{
	CellAlignment Alignments::normal(horizontal_alignment::left, vertical_alignment::center);
	CellAlignment Alignments::title(horizontal_alignment::center, vertical_alignment::center);

	CellAlignment::CellAlignment()
		: horizontal{ horizontal_alignment::left }, vertical{ vertical_alignment::top }
	{
	}

	CellAlignment::CellAlignment(horizontal_alignment horizontal, vertical_alignment vertical)
		: horizontal{ horizontal }, vertical{ vertical }
	{
	}

	CellAlignment::operator alignment()
	{
		alignment alignment;

		alignment.horizontal(horizontal);
		alignment.vertical(vertical);

		return alignment;
	}
}