//#pragma once
//
//#include <libxl/libxl.h>
//
//#include "Veridox.h"
//
//using libxl::Book;
//using libxl::Font;
//using libxl::Format;
//using libxl::Sheet;
//using libxl::AlignH;
//using libxl::AlignV;
//using libxl::AlignV;
//
//class ExcelHelper
//{
//private:
//	struct ColumnInfo
//	{
//	public:
//		const wchar_t* title;
//		int index;
//		double width;
//
//	};
//
//	struct FormatStyle
//	{
//	public:
//		const wchar_t* name;
//		int size;
//		AlignH horizontalAlign;
//		AlignV verticalAlign;
//		unsigned char style;
//
//	};
//
//public:
//	static void Init();
//	static void AddResultToBook(Veridox::TestResult& result);
//	static void Shutdown();
//
//private:
//	static int m_titleRowIndex;
//	static int m_totalRows;
//	static int m_totalColumns;
//
//	static Book* m_book;
//	static Sheet* m_sheet;
//
//	static Format* m_normalFormat;
//	static Format* m_idFormat;
//	static Format* m_successFormat;
//	static Format* m_failedFormat;
//	static Format* m_titleFormat;
//
//	static FormatStyle m_idStyle;
//	static FormatStyle m_normalStyle;
//	static FormatStyle m_titleStyle;
//
//	static vector<ColumnInfo> m_columns;
//
//private:
//	static void CreateColumn(ColumnInfo& info);
//
//	static void InitFormats();
//	static Format* MakeFormat(FormatStyle& style, Font* baseFont = nullptr);
//
//};