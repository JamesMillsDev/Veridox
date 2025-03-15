#include "Style.h"

#include <xlnt/styles/fill.hpp>

using xlnt::fill;

namespace Veridox::Private
{
	Style* Styles::title = nullptr;

	Style* Styles::normalBody[2] = { nullptr, nullptr };
	Style* Styles::id[2] = { nullptr, nullptr };

	Style* Styles::failed = nullptr;
	Style* Styles::succeeded = nullptr;

	Style::Style()
		: Style("Normal")
	{
	}

	Style::Style(const string& name)
		: Style(name, FontTypes::normal)
	{
	}

	Style::Style(const string& name, Font* font)
		: Style(name, font, 0x00000000)
	{
	}

	Style::Style(const string& name, Font* font, Color fill)
		: Style(name, font, fill, Alignments::normal)
	{
	}

	Style::Style(const string& name, Font* font, Color fill, CellAlignment* alignment)
		: Style(name, font, fill, alignment, BorderTypes::none)
	{
	}

	Style::Style(const string& name, Font* font, Color fill, CellAlignment* alignment, Border* border)
		: Style(name, font, fill, alignment, border, number_format::text())
	{
	}

	Style::Style(string name, Font* font, Color fill, CellAlignment* alignment, Border* border, number_format numberFormat)
		: name{ std::move(name) }, font{ font }, fill{ fill }, alignment{ alignment }, border{ border },
		numberFormat{ std::move(numberFormat) }
	{
	}

	style Style::ToExcel(style reference)
	{
		reference.name(name);

		reference.font(*font);
		if (fill.a == 255)
		{
			reference.fill(fill::solid(fill));
		}

		reference.alignment(*alignment);
		reference.border(*border);

		reference.number_format(numberFormat);

		return reference;
	}

	void Styles::Init()
	{
		BorderTypes::Init();
		FontTypes::Init();
		Alignments::Init();

		title = new Style("Title", FontTypes::title, 0x156082ff, Alignments::title, BorderTypes::title);

		normalBody[0] = new Style("Normal 1", FontTypes::normal, 0xd9d9d9ff, Alignments::normal, BorderTypes::none);
		normalBody[1] = new Style("Normal 2", FontTypes::normal, 0x00000000, Alignments::normal, BorderTypes::none);

		id[0] = new Style("ID 1", FontTypes::normal, 0xd9d9d9ff, Alignments::title, BorderTypes::none, number_format::number());
		id[1] = new Style("ID 2", FontTypes::normal, 0x00000000, Alignments::title, BorderTypes::none, number_format::number());

		failed = new Style("Failed Test", FontTypes::failed, 0xffc7ceff, Alignments::title, BorderTypes::none);
		succeeded = new Style("Succeeded Test", FontTypes::succeeded, 0xc6efceff, Alignments::title, BorderTypes::none);
	}

	void Styles::Shutdown()
	{
		delete title;

		delete normalBody[0];
		delete normalBody[1];

		delete id[0];
		delete id[1];

		delete failed;
		delete succeeded;

		Alignments::Shutdown();
		FontTypes::Shutdown();
		BorderTypes::Shutdown();
	}
}
