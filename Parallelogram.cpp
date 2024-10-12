#include "Parallelogram.h"

void Parallelogram::Draw(Board& board) const
{
	int xA = x0, yA = y0;
	int xB = x0 + width, yB = y0;
	int xC = x1, yC = y1;
	int xD = x1 - width, yD = y1;
	std::shared_ptr<Line> AB = std::make_shared<Line>(color, std::vector<int>{xA, yA, xB, yB});
	std::shared_ptr<Line> BC = std::make_shared<Line>(color, std::vector<int>{xB, yB, xC, yC});
	std::shared_ptr<Line> CD = std::make_shared<Line>(color, std::vector<int>{xC, yC, xD, yD});
	std::shared_ptr<Line> DA = std::make_shared<Line>(color, std::vector<int>{xD, yD, xA, yA});
	AB->Draw(board); BC->Draw(board); CD->Draw(board); DA->Draw(board);
}

void Parallelogram::Change(const std::vector<int>& params)
{
	if (params.size() != 5)
		throw std::invalid_argument("Invalid number of parameters for parallelogram");
	width = params[4]; x0 = params[0]; y0 = params[1]; x1 = params[2]; y1 = params[3];
}