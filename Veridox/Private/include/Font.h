#pragma once

#include <string>

#include <xlnt/styles/font.hpp>

#include "Color.h"

using std::string;

using xlnt::font;

namespace Veridox::Private
{
	typedef font& (font::* FontStyleSetter)(bool);

	using EUnderlineStyle = font::underline_style;

	enum EStyleFlags : uint8_t
	{
		None = 1 << 0,
		Bold = 1 << 1,
		Italic = 1 << 2,
		Strikethrough = 1 << 3,
		Superscript = 1 << 4,
		Subscript = 1 << 5
	};

	class Font
	{
	public:
		string name;
		double size;
		Color color;
		uint8_t styleFlags;
		EUnderlineStyle underlineStyle;

	public:
		Font();
		Font(const string& name);
		Font(const string& name, double size);
		Font(const string& name, double size, Color color);
		Font(const string& name, double size, Color color, uint8_t styleFlags);
		Font(string name, double size, Color color, uint8_t styleFlags, EUnderlineStyle underlineStyle);

	public:
		operator font();

	private:
		void SetFontStyle(font& f, EStyleFlags flag, FontStyleSetter setter) const;

	};

	class FontTypes
	{
	public:
		static Font* normal;
		static Font* title;

		static Font* failed;
		static Font* succeeded;

	public:
		static void Init();
		static void Shutdown();

	};
}