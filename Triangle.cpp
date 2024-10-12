#include "Triangle.h"
#include <ranges>

void Triangle::Draw(Board& board) const
{
	if (height == 0)
	{
		std::shared_ptr<Line> AB = std::make_shared<Line>(color, std::vector<int>{x, y, x + base, y});
		AB->Draw(board);
		return;
	}
	if (base == 0)
	{
		std::shared_ptr<Line> BC = std::make_shared<Line>(color, std::vector<int>{x, y + height, x, y});
		BC->Draw(board);
		return;
	}
	int xA = x, yA = y;
	int xB = x + base, yB = y;
	int xC = x + base / 2, yC = y - height;
	std::shared_ptr<Line> AB = std::make_shared<Line>(color, std::vector<int>{xA, yA, xB, yB});  // base
	std::shared_ptr<Line> BC = std::make_shared<Line>(color, std::vector<int>{xB, yB, xC, yC});  // side
	std::shared_ptr<Line> CA = std::make_shared<Line>(color, std::vector<int>{xC, yC, xA, yA});  // side
	AB->Draw(board); BC->Draw(board); CA->Draw(board);
	if (fill)
	{
		std::vector<std::tuple<int, int>> sideTrace0 = BC->Trace();
		std::vector<std::tuple<int, int>> sideTrace1 = CA->Trace();
		for (std::tuple points : std::views::zip(sideTrace0, sideTrace1))
		{
			std::tuple<int, int> point0 = std::get<0>(points), point1 = std::get<1>(points);
			int fX0 = std::get<0>(point0), fY0 = std::get<1>(point0);
			int fX1 = std::get<0>(point1), fY1 = std::get<1>(point1);
			std::shared_ptr<Line> filler = std::make_shared<Line>(color, std::vector<int>{fX0, fY0, fX1, fY1});
			filler->Draw(board);
		}
		
	}
}

void Triangle::Change(const std::vector<int>& params)
{
	if (params.size() != 4)
		throw std::invalid_argument("Invalid number of parameters for triangle");
	base = params[0];
	height = params[1];
	x = params[2];
	y = params[3];
}