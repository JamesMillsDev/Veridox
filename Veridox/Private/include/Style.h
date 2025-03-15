#pragma once

#include <xlnt/styles/style.hpp>
#include <xlnt/styles/number_format.hpp>

#include "Font.h"
#include "CellAlignment.h"
#include "Border.h"

using xlnt::number_format;
using xlnt::style;

namespace Veridox::Private
{
	class Style
	{
	public:
		string name;

		Font* font;
		Color fill;

		CellAlignment* alignment;
		Border* border;

		number_format numberFormat;

	public:
		Style();
		Style(const string& name);
		Style(const string& name, Font* font);
		Style(const string& name, Font* font, Color fill);
		Style(const string& name, Font* font, Color fill, CellAlignment* alignment);
		Style(const string& name, Font* font, Color fill, CellAlignment* alignment, Border* border);
		Style(string name, Font* font, Color fill, CellAlignment* alignment, Border* border, number_format numberFormat);

	public:
		style ToExcel(style reference);

	};

	class Styles
	{
	public:
		static Style* title;
		static Style* normalBody[2];
		static Style* id[2];

		static Style* failed;
		static Style* succeeded;

	public:
		static void Init();
		static void Shutdown();

	};
}