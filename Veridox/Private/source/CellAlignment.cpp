#include "CellAlignment.h"

namespace Veridox::Private
{
	CellAlignment* Alignments::normal = nullptr;
	CellAlignment* Alignments::title = nullptr;

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

	void Alignments::Init()
	{
		normal = new CellAlignment(horizontal_alignment::left, vertical_alignment::center);
		title = new CellAlignment(horizontal_alignment::center, vertical_alignment::center);
	}

	void Alignments::Shutdown()
	{
		delete normal;
		delete title;
	}
}
