#pragma once
#include "Parallelogram.h"

class Square : public Parallelogram
{
public:
	Square(const int InSide, const int InX, const int InY) : Parallelogram(InX, InY, InX + InSide, InY + InSide/2, InSide), side(InSide), x(InX), y(InY) {}
	~Square() = default;

	unsigned long long GetId() const override { return std::hash<int>{}(x + y + side); }
	std::string GetParameters() const override { return std::format("Square, start at {}, {} with side length {}", x, y, side); }
	std::string Dump() const override { return std::format("square {} {} {}", side, x, y); }
private:
	int side, x, y;
};