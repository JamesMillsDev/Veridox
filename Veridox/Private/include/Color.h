#pragma once

#include <xlnt/styles/color.hpp>

using xlnt::color;

namespace Veridox::Private
{
	class Color
	{
	public:
		uint8_t r;
		uint8_t g;
		uint8_t b;
		uint8_t a;

	public:
		Color();
		Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
		Color(uint32_t color);

	public:
		operator color();

	};
}