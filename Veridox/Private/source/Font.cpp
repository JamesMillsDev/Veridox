#include "Font.h"

#include <map>

using std::pair;

namespace Veridox::Private
{
	Font* FontTypes::normal = nullptr;
	Font* FontTypes::title = nullptr;

	Font* FontTypes::succeeded = nullptr;
	Font* FontTypes::failed = nullptr;

	pair<EStyleFlags, FontStyleSetter> setters[] =
	{
		{ Bold, &font::bold },
		{ Italic, &font::italic },
		{ Strikethrough, &font::strikethrough },
		{ Superscript, &font::superscript },
		{ Subscript, &font::subscript },
	};

	Font::Font()
		: Font("Calibri")
	{
	}

	Font::Font(const string& name)
		: Font(name, 12)
	{
	}

	Font::Font(const string& name, double size)
		: Font(name, size, 0xffffffff)
	{
	}

	Font::Font(const string& name, double size, Color color)
		: Font(name, size, color, None)
	{
	}

	Font::Font(const string& name, double size, Color color, uint8_t styleFlags)
		: Font(name, size, color, styleFlags, EUnderlineStyle::none)
	{
	}

	Font::Font(string name, double size, Color color, uint8_t styleFlags, EUnderlineStyle underlineStyle)
		: name{ std::move(name) }, size{ size }, color{ color }, styleFlags{ styleFlags }, underlineStyle{ underlineStyle }
	{
	}

	Font::operator font()
	{
		font f;

		for (auto [flag, fnc] : setters)
		{
			SetFontStyle(f, flag, fnc);
		}

		f.underline(underlineStyle);
		f.size(size);
		f.color(color);

		return f;
	}

	void Font::SetFontStyle(font& f, EStyleFlags flag, FontStyleSetter setter) const
	{
		(f.*setter)((styleFlags & flag) == flag);
	}

	void FontTypes::Init()
	{
		normal = new Font("Calibri", 12, 0x000000ff, Bold, EUnderlineStyle::none);
		title = new Font("Calibri", 24, 0xffffffff, None, EUnderlineStyle::none);

		succeeded = new Font("Calibri", 12, 0x006100ff, None, EUnderlineStyle::none);
		failed = new Font("Calibri", 12, 0x9c0006ff, None, EUnderlineStyle::none);
	}

	void FontTypes::Shutdown()
	{
		delete normal;
		delete title;

		delete succeeded;
		delete failed;
	}
}
