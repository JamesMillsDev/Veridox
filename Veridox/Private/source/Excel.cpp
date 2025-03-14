#include "Excel.h"

#include <cassert>
#include <filesystem>

using xlnt::path;
using xlnt::worksheet;

namespace Veridox::Private
{
	Excel::Excel(const string& wbName)
		: m_workbook{ nullptr }, m_workbookName{ wbName }
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
	}

	void Excel::Close()
	{
		assert(m_workbook != nullptr && "Workbook shouldn't be nullptr!");

		m_workbook->save(m_workbookName);

		for (auto& sheet : m_sheets)
		{
			delete sheet;
		}

		m_sheets.clear();

		delete m_workbook;
	}

	Sheet* Excel::GetSheet(const string& name)
	{
		if (m_workbook == nullptr)
		{
			return nullptr;
		}

		for (const auto& sheet : m_sheets)
		{
			if (sheet->Name() == name)
			{
				return sheet;
			}
		}

		worksheet sheet = m_workbook->active_sheet();
		sheet.title(name);

		Sheet* newSheet = new Sheet(sheet);
		m_sheets.emplace_back(newSheet);

		return newSheet;
	}
}