#pragma once

#include <string>

#include <xlnt/cell/cell.hpp>
#include <xlnt/utils/datetime.hpp>

#include "Style.h"

using std::string;

using xlnt::cell;
using xlnt::datetime;
using xlnt::worksheet;

namespace Veridox::Private
{
	class Cell
	{
	public:
		uint32_t column;
		uint32_t row;

	public:
		Cell(uint32_t column, uint32_t row, worksheet ws);
		Cell(cell& cell);

	public:
		void Set(uint32_t value);
		void Set(const string& value);
		void Set(datetime value);

		void SetStyle(Style& style);

	private:
		cell m_cell;

	};
}