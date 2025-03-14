#include "Font.h"

#include <map>

using std::pair;

namespace Veridox::Private
{
	Font FontTypes::normal("Calibri", 12, 0x000000ff, EStyleFlags::Bold, EUnderlineStyle::none);
	Font FontTypes::title("Calibri", 24, 0xffffffff, EStyleFlags::None, EUnderlineStyle::none);

	Font FontTypes::succeeded("Calibri", 12, 0x006100ff, EStyleFlags::None, EUnderlineStyle::none);
	Font FontTypes::failed("Calibri", 12, 0x9c0006ff, EStyleFlags::None, EUnderlineStyle::none);

	pair<EStyleFlags, FontStyleSetter> setters[] =
	{
		{ EStyleFlags::Bold, &font::bold },
		{ EStyleFlags::Italic, &font::italic },
		{ EStyleFlags::Strikethrough, &font::strikethrough },
		{ EStyleFlags::Superscript, &font::superscript },
		{ EStyleFlags::Subscript, &font::subscript },
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
		: Font(name, 12, 0xffffffff)
	{
	}

	Font::Font(const string& name, double size, Color color)
		: Font(name, size, color, EStyleFlags::None)
	{
	}

	Font::Font(const string& name, double size, Color color, uint8_t styleFlags)
		: Font(name, size, color, styleFlags, EUnderlineStyle::none)
	{
	}

	Font::Font(const string& name, double size, Color color, uint8_t styleFlags, EUnderlineStyle underlineStyle)
		: name{ name }, size{ size }, color{ color }, styleFlags{ styleFlags }, underlineStyle{ underlineStyle }
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

	void Font::SetFontStyle(font& f, EStyleFlags flag, FontStyleSetter setter)
	{
		(f.*setter)((styleFlags & flag) == flag);
	}
}