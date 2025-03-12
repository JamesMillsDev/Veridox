//#include "ExcelHelper.h"
//
//#include <format>
//#include <Windows.h>
//
//using std::wstring;
//
//int ExcelHelper::m_titleRowIndex = 1;
//int ExcelHelper::m_totalColumns = 16384;
//
//Book* ExcelHelper::m_book = nullptr;
//Sheet* ExcelHelper::m_sheet = nullptr;
//
//Format* ExcelHelper::m_normalFormat = nullptr;
//Format* ExcelHelper::m_idFormat = nullptr;
//Format* ExcelHelper::m_successFormat = nullptr;
//Format* ExcelHelper::m_failedFormat = nullptr;
//Format* ExcelHelper::m_titleFormat = nullptr;
//
//ExcelHelper::FormatStyle ExcelHelper::m_idStyle =
//{
//	L"Calibri",
//	14,
//	AlignH::ALIGNH_CENTER,
//	AlignV::ALIGNV_CENTER,
//	0x00
//};
//ExcelHelper::FormatStyle ExcelHelper::m_normalStyle =
//{
//	L"Calibri",
//	14,
//	AlignH::ALIGNH_LEFT,
//	AlignV::ALIGNV_CENTER,
//	0x00
//};
//ExcelHelper::FormatStyle ExcelHelper::m_titleStyle =
//{
//	nullptr,
//	25,
//	AlignH::ALIGNH_CENTER,
//	AlignV::ALIGNV_CENTER,
//	0x00 | 0x01
//};
//
//vector<ExcelHelper::ColumnInfo> ExcelHelper::m_columns =
//{
//	{ L"ID", 0, 5.5 },
//	{ L"Name", 1, 14 },
//	{ L"Result", 2, 14 },
//	{ L"Error Message", 3, 100 }
//};
//
//inline wstring Convert(const string& as)
//{
//	// deal with trivial case of empty string
//	if (as.empty())
//	{
//		return std::wstring();
//	}
//
//	// determine required length of new string
//	size_t reqLength = ::MultiByteToWideChar(CP_UTF8, 0, as.c_str(), (int)as.length(), 0, 0);
//
//	// construct new string of required length
//	std::wstring ret(reqLength, L'\0');
//
//	// convert old string to new string
//	::MultiByteToWideChar(CP_UTF8, 0, as.c_str(), (int)as.length(), &ret[0], (int)ret.length());
//
//	// return new string ( compiler should optimize this away )
//	return ret;
//}
//
//void ExcelHelper::Init()
//{
//	m_book = xlCreateBook();
//	m_book->setRgbMode(true);
//
//	m_sheet = m_book->addSheet(L"Results");
//	for (int i = m_columns.back().index + 1; i < m_totalColumns; ++i)
//	{
//		m_sheet->setColHidden(i, true);
//	}
//
//	InitFormats();
//
//	for (ColumnInfo& column : m_columns)
//	{
//		CreateColumn(column);
//	}
//}
//
//void ExcelHelper::AddResultToBook(Veridox::TestResult& result)
//{
//	Format* resultFormat = result.success ? m_successFormat : m_failedFormat;
//
//	m_sheet->writeStr(result.id + 1, 0, Convert(std::format("{:0>3}", result.id)).c_str(), m_idFormat);
//	m_sheet->writeStr(result.id + 1, 1, Convert(std::format("{}", result.name)).c_str(), m_normalFormat);
//	m_sheet->writeStr(result.id + 1, 2, Convert(std::format("{}", result.success ? "Successful" : "Failed")).c_str(), resultFormat);
//	m_sheet->writeStr(result.id + 1, 3, Convert(std::format("{}", result.failReason)).c_str(), m_normalFormat);
//}
//
//void ExcelHelper::Shutdown()
//{
//	m_book->save(L"Results.xls");
//	m_book->release();
//}
//
//void ExcelHelper::CreateColumn(ColumnInfo& info)
//{
//	m_sheet->setCol(info.index, info.index, info.width, m_titleFormat);
//	m_sheet->writeStr(m_titleRowIndex, info.index, info.title);
//}
//
//void ExcelHelper::InitFormats()
//{
//	m_normalFormat = MakeFormat(m_normalStyle);
//	m_idFormat = MakeFormat(m_idStyle, m_normalFormat->font());
//	m_titleFormat = MakeFormat(m_titleStyle, m_normalFormat->font());
//
//	m_successFormat = MakeFormat(m_normalStyle, m_normalFormat->font());
//	m_successFormat->setFillPattern(libxl::FILLPATTERN_SOLID);
//	m_successFormat->setPatternForegroundColor(m_book->colorPack(198, 239, 206));
//	m_successFormat->font()->setColor(m_book->colorPack(0, 97, 0));
//
//	m_failedFormat = MakeFormat(m_normalStyle, m_normalFormat->font());
//	m_failedFormat->setFillPattern(libxl::FILLPATTERN_SOLID);
//	m_failedFormat->setPatternForegroundColor(m_book->colorPack(255, 199, 206));
//	m_failedFormat->font()->setColor(m_book->colorPack(156, 0, 6));
//}
//
//Format* ExcelHelper::MakeFormat(FormatStyle& style, Font* baseFont)
//{
//	Font* font = m_book->addFont(baseFont);
//	font->setSize(style.size);
//
//	if (baseFont == nullptr)
//	{
//		font->setName(style.name);
//	}
//
//	if ((style.style & 0x01) == 0x01)
//	{
//		font->setBold();
//	}
//
//	if ((style.style & 0x02) == 0x02)
//	{
//		font->setItalic();
//	}
//
//	if ((style.style & 0x03) == 0x03)
//	{
//		font->setUnderline(libxl::Underline::UNDERLINE_SINGLE);
//	}
//
//	if ((style.style & 0x04) == 0x04)
//	{
//		font->setStrikeOut();
//	}
//
//	Format* fmt = m_book->addFormat();
//	fmt->setFont(font);
//	fmt->setAlignH(style.horizontalAlign);
//	fmt->setAlignV(style.verticalAlign);
//
//	return fmt;
//}
