#include "Circle.h"

void Circle::Draw(Board& board) const // https://zingl.github.io/bresenham.html#:~:text=This%20page%20introduces%20a%20compact%20and%20efficient%20implementation%20of%20Bresenham's
{
    int oX = x, oY = y, r;
    int xI = -radius, yI = 0;
    int error = 2 - 2 * radius;
    int k = 2;
    do
    {
        board.SetPixel(oX - xI * k, oY + yI);
        board.SetPixel(oX - yI * k, oY - xI);
        board.SetPixel(oX + xI * k, oY - yI);
        board.SetPixel(oX + yI * k, oY + xI);
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