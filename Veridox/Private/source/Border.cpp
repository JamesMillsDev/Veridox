#include "Border.h"

namespace Veridox::Private
{
	Border BorderTypes::none
	{
		map<EBorderSide, Border::Property>
		{
			{ EBorderSide::top, Border::Property(0x00000000, EBorderStyle::none) },
			{ EBorderSide::bottom, Border::Property(0x00000000, EBorderStyle::none) },
			{ EBorderSide::start, Border::Property(0x00000000, EBorderStyle::none) },
			{ EBorderSide::end, Border::Property(0x00000000, EBorderStyle::none) },
		}
	};
	Border BorderTypes::all
	{
		map<EBorderSide, Border::Property>
		{
			{ EBorderSide::top, Border::Property(0xd9d9d9ff, EBorderStyle::thin) },
			{ EBorderSide::bottom, Border::Property(0xd9d9d9ff, EBorderStyle::thin) },
			{ EBorderSide::start, Border::Property(0xd9d9d9ff, EBorderStyle::thin) },
			{ EBorderSide::end, Border::Property(0xd9d9d9ff, EBorderStyle::thin) },
		}
	};

	Border BorderTypes::title =
	{
		map<EBorderSide, Border::Property>
		{
			{ EBorderSide::bottom, Border::Property(0x000000ff, EBorderStyle::thick) }
		}
	};

	Border::Property::Property()
		: Property(0xffffffff)
	{
	}

	Border::Property::Property(Color color)
		: Property(color, EBorderStyle::none)
	{
	}

	Border::Property::Property(Color color, EBorderStyle style)
		: color{ color }, style{ style }
	{
	}

	Border::Property::operator border::border_property()
	{
		border::border_property prop;

		prop.color(color);
		prop.style(style);

		return prop;
	}

	Border::Border()
	{

	}

	Border::Border(map<EBorderSide, Property> sides)
		: sides{ sides }
	{
	}

	Border::operator border()
	{
		border b;

		TrySetBorderSide(b, EBorderSide::top);
		TrySetBorderSide(b, EBorderSide::bottom);
		TrySetBorderSide(b, EBorderSide::start);
		TrySetBorderSide(b, EBorderSide::end);

		return b;
	}

	void Border::TrySetBorderSide(border& b, EBorderSide side)
	{
		if (sides.contains(side))
		{
			b.side(side, sides[side]);
		}
	}
}