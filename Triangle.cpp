#include "Triangle.h"

void Triangle::Draw(Board& board) const
{
	if (height == 0)
	{
		std::shared_ptr<Line> AB = std::make_shared<Line>(std::vector<int>{x, y, x + base, y});
		AB->Draw(board);
		return;
	}
	if (base == 0)
	{
		std::shared_ptr<Line> BC = std::make_shared<Line>(std::vector<int>{x, y + height, x, y});
		BC->Draw(board);
		return;
	}
	int xA = x, yA = y;
	int xB = x + base, yB = y;
	int xC = x + base / 2, yC = y - height;
	std::shared_ptr<Line> AB = std::make_shared<Line>(std::vector<int>{xA, yA, xB, yB});
	std::shared_ptr<Line> BC = std::make_shared<Line>(std::vector<int>{xB, yB, xC, yC});
	std::shared_ptr<Line> CA = std::make_shared<Line>(std::vector<int>{xC, yC, xA, yA});
	AB->Draw(board); BC->Draw(board); CA->Draw(board);
}

void Triangle::Change(const std::vector<int>& params)
{
	base = params[0];
	height = params[1];
	x = params[2];
	y = params[3];
}