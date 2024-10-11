#pragma once
#include "Shape.h"
#include "Board.h"
#include "Line.h"

class Parallelogram : public Shape
{
public:
	Parallelogram(const std::vector<int>& params) :
		width(params[4]), x0(params[0]), y0(params[1]), x1(params[2]), y1(params[3]), id(std::hash<std::string>{}(this->GetParameters())) {}
	~Parallelogram() = default;
	void Draw(Board& board) const override;

	unsigned long long GetId() const override { return id; }
	std::string GetParameters() const override { return std::format("Parallelogram, between A({}, {}) and B({}, {}) with base width {}", x0, y0, x1, y1, width); }
	std::string Dump() const override { return std::format("parallelogram {} {} {} {} {}", x0, y0, x1, y1, width); }
private:
	int width, x0, y0, x1, y1;
	unsigned long long id;
};