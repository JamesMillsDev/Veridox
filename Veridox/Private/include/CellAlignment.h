#pragma once

#include <xlnt/styles/alignment.hpp>

using xlnt::alignment;
using xlnt::horizontal_alignment;
using xlnt::vertical_alignment;

namespace Veridox::Private
{
	class CellAlignment
	{
	public:
		horizontal_alignment horizontal;
		vertical_alignment vertical;

	public:
		CellAlignment();
		CellAlignment(horizontal_alignment horizontal, vertical_alignment vertical);

	public:
		operator alignment();

	};

	class Alignments
	{
	public:
		static CellAlignment normal;
		static CellAlignment title;

	};
}