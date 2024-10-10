#pragma once
#include "Board.h"

class Circle : public Shape
{
public:
	Circle(const unsigned int InRadius, const unsigned int InX, const unsigned int InY) : radius(InRadius), x(InX), y(InY) {}
	~Circle() = default;
	void Draw(Board& board) const override;

	unsigned long long GetId() const override { return std::hash<unsigned int>{}(radius + x + y); }
	std::string GetParameters() const override { return std::format("Circle, radius {}, start at X{}, Y{}", radius, x, y); }
	std::string Dump() const override { return std::format("circle {} {} {}", radius, x, y); }
private:
	int radius;
	unsigned int x, y;
};