#pragma once
#include "Parallelogram.h"

class Rectangle : public Parallelogram
{
public:
    Rectangle(const std::vector<int>& params) :
        Parallelogram({params[2], params[3], params[2] + params[0], params[3] + params[1], params[0]}),
        width(params[0]), height(params[1]), x(params[2]), y(params[3]), id(std::hash<std::string>{}(this->Dump())) {}
    ~Rectangle() = default;

	void Change(const std::vector<int>& params) override 
    { 
		if (params.size() != 4)
			throw std::invalid_argument("Invalid number of parameters");
        width = params[0]; height = params[1]; x = params[2]; y = params[3]; 
        Parallelogram::Change({ x, y, x + width, y + height, width }); 
    }

	std::string Dump() const override { return std::format("rectangle {} {} {} {}", width, height, x, y); }
    unsigned long long GetId() const override { return id; }
	int GetWidth() const { return width; }
	int GetHeight() const { return height; }
	int GetX() const { return x; }
	int GetY() const { return y; }

private:
    int width, height, x, y;
	unsigned long long id;
};