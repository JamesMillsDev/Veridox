#include "Style.h"

#include <xlnt/styles/fill.hpp>

using xlnt::fill;

namespace Veridox::Private
{
	Style Styles::title("Title", &FontTypes::title, 0x156082ff, &Alignments::title, &BorderTypes::title);

	Style Styles::normalBody[2] =
	{
		Style("Normal 1", &FontTypes::normal, 0xd9d9d9ff, &Alignments::normal, &BorderTypes::none),
		Style("Normal 2", &FontTypes::normal, 0xffffffff, &Alignments::normal, &BorderTypes::none)
	};

	Style Styles::id[2] =
	{
		Style("ID 1", &FontTypes::normal, 0xd9d9d9ff, &Alignments::title, &BorderTypes::none, number_format::number_00()),
		Style("ID 2", &FontTypes::normal, 0xffffffff, &Alignments::title, &BorderTypes::none, number_format::number_00())
	};

	Style Styles::failed("Failed Test", &FontTypes::failed, 0xffc7ceff, &Alignments::title, &BorderTypes::none);
	Style Styles::succeeded("Succeeded Test", &FontTypes::succeeded, 0xc6efceff, &Alignments::title, &BorderTypes::none);

	Style::Style()
		: Style("Normal")
	{
	}

	Style::Style(const string& name)
		: Style(name, &FontTypes::normal)
	{
	}

	Style::Style(const string& name, Font* font)
		: Style(name, font, 0x00000000)
	{
	}

	Style::Style(const string& name, Font* font, Color fill)
		: Style(name, font, fill, &Alignments::normal)
	{
	}

	Style::Style(const string& name, Font* font, Color fill, CellAlignment* alignment)
		: Style(name, font, fill, alignment, &BorderTypes::none)
	{
	}

	Style::Style(const string& name, Font* font, Color fill, CellAlignment* alignment, Border* border)
		: Style(name, font, fill, alignment, border, number_format::text())
	{
	}

	Style::Style(const string& name, Font* font, Color fill, CellAlignment* alignment, Border* border, number_format numberFormat)
		: name{ name }, font{ font }, fill{ fill }, alignment{ alignment }, border{ border }, numberFormat{ numberFormat }
	{
	}

	style Style::ToExcel(style reference)
	{
		reference.name(name);

		reference.font(*font);
		reference.fill(fill::solid(fill));

		reference.alignment(*alignment);
		reference.border(*border);

		reference.number_format(numberFormat);

		return reference;
	}
}