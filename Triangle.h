#pragma once
#include "Shape.h"
#include "Board.h"
#include "Line.h"

class Triangle : public Shape
{
public:
	Triangle(const unsigned int InBase, const unsigned int InHeight, const unsigned int InX, const unsigned int InY) : 
		base(InBase), height(InHeight), x(InX), y(InY) {}
	~Triangle() = default;
	void Draw(Board& board) const override;

	unsigned long long GetId() const override { return std::hash<unsigned int>{}(base + height + x + y); }
	std::string GetParameters() const override { return std::format("Triangle, base {}, height {}, start at X{}, Y{}", base, height, x, y); }
	std::string Dump() const override { return std::format("triangle {} {} {} {}", base, height, x, y); }
private:
	unsigned int base, height, x, y;
};