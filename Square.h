#pragma once
#include "Parallelogram.h"

class Square : public Parallelogram
{
public:
	Square(const std::vector<int>& params) : 
		Parallelogram({params[0], params[1], params[0] + params[2], params[1] + params[2], params[2]}), side(params[2]), 
		x(params[0]), y(params[1]), id(std::hash<std::string>{}(this->Dump())) {}
	~Square() = default;

	void Change(const std::vector<int>& params) override 
	{
		if (params.size() != 3) 
			throw std::invalid_argument("Invalid number of parameters");
		side = params[2]; x = params[0]; y = params[1]; 
		Parallelogram::Change({ x, y, x + side, y + side, side }); 
	}

	std::string Dump() const override { return std::format("square {} {} {}", side, x, y); }
	unsigned long long GetId() const override { return id; }
	int GetSide() const { return side; }
	int GetX() const { return x; }
	int GetY() const { return y; }
private:
	int side, x, y;
	unsigned long long id;
};