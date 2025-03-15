#pragma once

#include <map>

#include <xlnt/styles/border.hpp>

#include "Color.h"

using std::map;

using xlnt::border;
using EBorderSide = xlnt::border_side;
using EBorderStyle = xlnt::border_style;

namespace Veridox::Private
{
	class Border
	{
	public:
		struct Property
		{
		public:
			Color color;
			EBorderStyle style;

		public:
			Property();
			Property(Color color);
			Property(Color color, EBorderStyle style);

		public:
			operator border::border_property();

		};

	public:
		map<EBorderSide, Property> sides;

	public:
		Border();
		Border(map<EBorderSide, Property> sides);

	public:
		operator border();

	private:
		void TrySetBorderSide(border& b, EBorderSide side);

	};

	class BorderTypes
	{
	public:
		static Border* none;
		static Border* all;
		static Border* title;

	public:
		static void Init();
		static void Shutdown();

	};
}