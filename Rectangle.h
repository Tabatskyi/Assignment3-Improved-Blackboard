#pragma once
#include "Parallelogram.h"

class Rectangle : public Parallelogram
{
public:
	Rectangle(const bool InFill, const std::string& InColor, const std::vector<int>& params) : 
		Parallelogram(InFill, InColor, { params[2], params[3], params[2] + params[0], params[3] + params[1], params[0] }),
		fill(InFill), color(InColor), width(params[0]), height(params[1]), x(params[2]), y(params[3]), id(this->GetId()) {}
    ~Rectangle() = default;

	void Change(const std::vector<int>& params) override 
    { 
		if (params.size() != 4)
			throw std::invalid_argument("Invalid number of parameters");
        width = params[0]; height = params[1]; x = params[2]; y = params[3]; 
        Parallelogram::Change({ x, y, x + width, y + height, width }); 
    }

	std::string Dump() const override { return std::format("rectangle {} {} {} {} {} {}", this->GetFill(), color, width, height, x, y); }
	int GetWidth() const { return width; }
	int GetHeight() const { return height; }
	int GetX() const { return x; }
	int GetY() const { return y; }
private:
	bool fill;
	std::string color;
    int width, height, x, y;
	unsigned long long id;
};