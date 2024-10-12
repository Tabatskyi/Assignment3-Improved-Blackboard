#include "Line.h"

void Line::Draw(Board& board) const
{
	int x0 = xA, y0 = yA, x1 = xB, y1 = yB;
	if (x0 == x1)  // vertical line
	{
		if (y0 > y1)
			std::swap(y0, y1);
		for (int y = y0; y <= y1; y++)
			board.SetPixel(x0, y, color);
	}
	else if (y0 == y1)  // horizontal line
	{
		if (x0 > x1)
			std::swap(x0, x1);
		for (int x = x0; x <= x1; x++)
			board.SetPixel(x, y0, color);
	}
    // https://www.geeksforgeeks.org/bresenhams-line-generation-algorithm/
    // https://zingl.github.io/bresenham.html#:~:text=This%20page%20introduces%20a%20compact%20and%20efficient%20implementation%20of%20Bresenham's
	else
	{
        bool steep = abs(y1 - y0) > abs(x1 - x0);

        if (steep) 
        {
            std::swap(x0, y0);
            std::swap(x1, y1);
        }

        if (x0 > x1) 
        {
            std::swap(x0, x1);
            std::swap(y0, y1);
        }

        int dX = abs(x1 - x0), dY = abs(y1 - y0);
        int error = 2 * dY - dX;
        int yStep = (y0 < y1) ? 1 : -1;

        for (int x = x0, y = y0; x <= x1; x++) 
        {
            if (steep) 
                board.SetPixel(y, x, color);
            else 
                board.SetPixel(x, y, color);

            error -= dY;
            if (error < 0) 
            {
                y += yStep;
                error += dX;
            }
        }
	}
}

void Line::Change(const std::vector<int>& params)
{
    if (params.size() != 4)
		throw std::invalid_argument("Invalid number of parameters for line"); 
    xA = params[0]; yA = params[1]; xB = params[2]; yB = params[3];
}