#include "Triangle.h"

void Triangle::Draw(Board& board) const
{
	if (height == 0)
	{
		std::shared_ptr<Line> AB = std::make_unique<Line>(x, y, x + base, y);
		AB->Draw(board);
		return;
	}
	if (base == 0)
	{
		std::shared_ptr<Line> BC = std::make_unique<Line>(x, y + height, x, y);
		BC->Draw(board);
		return;
	}
	int xA = x, yA = y;
	int xB = x + base, yB = y;
	int xC = x + base / 2, yC = y - height;
	std::shared_ptr<Line> AB = std::make_unique<Line>(xA, yA, xB, yB);
	std::shared_ptr<Line> BC = std::make_unique<Line>(xB, yB, xC, yC);
	std::shared_ptr<Line> CA = std::make_unique<Line>(xC, yC, xA, yA);
	AB->Draw(board); BC->Draw(board); CA->Draw(board);
}