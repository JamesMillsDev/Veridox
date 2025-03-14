#include "Color.h"

enum EBitOffsets
{
	Red = 24,
	Green = 16,
	Blue = 8,
	Alpha = 0
};

namespace Veridox::Private
{
	Color::Color()
		: r{ 255 }, g{ 255 }, b{ 255 }, a{ 255 }
	{
	}

	Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
		: r{ r }, g{ g }, b{ b }, a{ a }
	{
	}

	Color::Color(uint32_t color)
		: r{ (color >> EBitOffsets::Red) & 0xff }, g{ (color >> EBitOffsets::Green) & 0xff },
		b{ (color >> EBitOffsets::Blue) & 0xff }, a{ (color >> EBitOffsets::Alpha) & 0xff }
	{
	}

	Color::operator color()
	{
		return color({ r, g, b, a });
	}
}