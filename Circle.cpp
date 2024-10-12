#include "Circle.h"

void Circle::Draw(Board& board) const // https://zingl.github.io/bresenham.html#:~:text=This%20page%20introduces%20a%20compact%20and%20efficient%20implementation%20of%20Bresenham's
{
    int oX = x, oY = y, r;
	for (int i = 0; i < radius && fill; i++)
	{
		int xI = -i, yI = 0;
		int error = 2 - 2 * i;
		int k = 2;
		do
		{
			board.SetPixel(oX - xI * k, oY + yI, color);
			board.SetPixel(oX - yI * k, oY - xI, color);
			board.SetPixel(oX + xI * k, oY - yI, color);
			board.SetPixel(oX + yI * k, oY + xI, color);
			r = error;
			if (r <= yI)
			{
				yI++;
				error += yI * 2 + 1;
			}
			if (r > xI || error > yI)
			{
				xI++;
				error += xI * 2 + 1;
			}
		} while (xI < 0);
	}
}

void Circle::Change(const std::vector<int>& params)
{
	if (params.size() != 3)
		throw std::invalid_argument("Invalid number of parameters for circle");
	radius = params[0]; x = params[1]; y = params[2];
}