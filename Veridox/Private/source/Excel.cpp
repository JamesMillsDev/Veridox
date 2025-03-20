#include "Excel.h"

#include <cassert>
#include <filesystem>

#include <xlnt/cell/cell.hpp>
#include <xlnt/worksheet/column_properties.hpp>

#include "Style.h"

using xlnt::cell_reference;
using xlnt::column_t;
using xlnt::path;

namespace Veridox::Private
{
	static uint32_t columnIndex = 1;

	Excel::Excel(string wbName)
		: m_workbook{ nullptr }, m_workbookName{ std::move(wbName) }
	{
	}

	void Excel::Open()
	{
		assert(m_workbook == nullptr && "Workbook shouldn't be nullptr!");

		if (std::filesystem::exists(m_workbookName))
		{
			m_workbook = new workbook(path("./" + m_workbookName));
		}
		else
		{
			m_workbook = new workbook();
		}

		m_worksheet = m_workbook->active_sheet();
		m_worksheet.title("Tests");
	}

	void Excel::Close() const
	{
		assert(m_workbook != nullptr && "Workbook shouldn't be nullptr!");

		for (auto& [id, style] : m_cachedStyles)
		{
			delete style;
		}

		m_workbook->save(m_workbookName);

		delete m_workbook;
	}

	void Excel::Set(uint32_t column, uint32_t row, uint32_t value, Style* style)
	{
		cell_reference ref(column_t(column), row);

		if (style != nullptr)
		{
			string styleName = style->name;

			if (!m_cachedStyles.contains(styleName))
			{
				m_cachedStyles[styleName] = new xlnt::style(m_workbook->create_style(styleName));
			}

			m_worksheet.cell(ref).style(style->ToExcel(*m_cachedStyles[styleName]));
		}

		m_worksheet.cell(ref).value(value);
	}

	void Excel::Set(uint32_t column, uint32_t row, string value, Style* style)
	{
		cell_reference ref(column_t(column), row);

		if (style != nullptr)
		{
			string styleName = style->name;

			if (!m_cachedStyles.contains(styleName))
			{
				m_cachedStyles[styleName] = new xlnt::style(m_workbook->create_style(styleName));
			}

			m_worksheet.cell(ref).style(style->ToExcel(*m_cachedStyles[styleName]));
		}

		m_worksheet.cell(ref).value(value);
	}

	uint32_t Excel::MakeCategory(const string& id, double width)
	{
		assert(m_workbook && "Workbook must be opened!");

		cell_reference ref(column_t(columnIndex++), 1);

		Set(ref.column_index(), ref.row(), id, Styles::title);
		m_worksheet.column_properties(ref.column()).width = width;

		return ref.column_index();
	}
}
