#pragma once
#include "Parallelogram.h"

class Rectangle : public Parallelogram
{
public:
	Rectangle(const int InWidth, const int InHeight, const int InX, const int InY) : 
        Parallelogram(InX, InY, InX + InWidth, InY + InHeight, InWidth), width(InWidth), height(InHeight), x(InX), y(InY) {}
    ~Rectangle() = default;

    unsigned long long GetId() const override { return std::hash<int>{}(x + y + width + height); }
	std::string GetParameters() const override { return std::format("Rectangle, start at {}, {} with base width {} and height {}", x, y, width, height); }
	std::string Dump() const override { return std::format("rectangle {} {} {} {}", width, height, x, y); }
private:
    int width, height, x, y;
};