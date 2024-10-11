#pragma once
#include "Shape.h"
#include "Board.h"
#include "Line.h"

class Parallelogram : public Shape
{
public:
	Parallelogram(const std::vector<int>& params) :
		width(params[4]), x0(params[0]), y0(params[1]), x1(params[2]), y1(params[3]), id(std::hash<std::string>{}(this->Dump())) {}
	~Parallelogram() = default;
	void Draw(Board& board) const override;
	void Change(const std::vector<int>& params) override;

	std::string Dump() const override { return std::format("parallelogram {} {} {} {} {}", x0, y0, x1, y1, width); }
	unsigned long long GetId() const override { return id; }
	int GetWidth() const { return width; }
	int GetX0() const { return x0; }
	int GetY0() const { return y0; }
	int GetX1() const { return x1; }
	int GetY1() const { return y1; }
private:
	int width, x0, y0, x1, y1;
	unsigned long long id;
};