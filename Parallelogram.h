#pragma once
#include "Shape.h"
#include "Board.h"
#include "Line.h"

class Parallelogram : public Shape
{
public:
	Parallelogram(const int InX0, const int InY0, const int InX1, const int InY1, const int InWidth) :
		width(InWidth), x0(InX0), y0(InY0), x1(InX1), y1(InY1) {}
	~Parallelogram() = default;
	void Draw(Board& board) const override;

	unsigned long long GetId() const override { return std::hash<int>{}(x0 + y0 + x1 + y1); }
	std::string GetParameters() const override { return std::format("Parallelogram, between A({}, {}) and B({}, {}) with base width {}", x0, y0, x1, y1, width); }
	std::string Dump() const override { return std::format("parallelogram {} {} {} {} {}", x0, y0, x1, y1, width); }
private:
	int width, x0, y0, x1, y1;
};