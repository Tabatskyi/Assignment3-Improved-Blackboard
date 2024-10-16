#pragma once
#include "Parallelogram.h"

class Square : public Parallelogram
{
public:
	Square(const bool InFill, const std::string& InColor, const std::vector<int>& params) : 
		Parallelogram(InFill, InColor, { params[0], params[1], params[0] + params[2] * 2, params[1] + params[2], params[2] * 2 }),
		fill(InFill), color(InColor), side(params[2]), x(params[0]), y(params[1]), id(this->GetId()) {}
	~Square() = default;

	void Change(const std::vector<int>& params) override 
	{
		if (params.size() != 3) 
			throw std::invalid_argument("Invalid number of parameters");
		side = params[2]; x = params[0]; y = params[1]; 
		Parallelogram::Change({ x, y, x + side * 2, y + side, side * 2 }); 
	}

	std::string Dump() const override { return std::format("square {} {} {} {} {}", this->GetFill(), color, side, x, y); }
	int GetSide() const { return side; }
	int GetX() const { return x; }
	int GetY() const { return y; }
private:
	bool fill;
	std::string color;
	int side, x, y;
	unsigned long long id;
};